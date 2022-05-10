
/*
 * Copyright (C) 2018 by IMDEA Networks Institute
 *
 * This file is part of Electrosense.
 *
 * Electrosense is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Electrosense is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with RTL-Spec.  If not, see <http://www.gnu.org/licenses/>.
 *
 * 	Authors:
 * 	    Roberto Calvo-Palomino <roberto.calvo@imdea.org>
 *
 */

#include "rtlsdrDriver.h"
#include <pthread.h>

//NEW
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <sstream>

#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstdlib>
#include <experimental/filesystem>
#include <dirent.h>


namespace electrosense {

rtlsdrDriver::rtlsdrDriver() {

  mQueueOut = new ReaderWriterQueue<SpectrumSegment *>(100);
  mQueueOut2 = new ReaderWriterQueue<SpectrumSegment *>(100);
  mConverterEnabled = false;
}

int rtlsdrDriver::open(std::string device) {
  // Start timers
  clock_gettime(CLOCK_REALTIME, &tinit);
  duration = ElectrosenseContext::getInstance()->getMonitorTime();

  // rtlsdr lib expects to have integer id for identifying the device
  mDeviceId = std::stoi(device);

  int device_index = mDeviceId;

  int n_rtlsdr = rtlsdr_get_device_count();

  if (n_rtlsdr == 0) {
    std::cerr << "* Error: no RTL-SDR USB devices found" << std::endl;
    throw std::logic_error("Fatal Error");
  }

  // Choose which device to use
  if ((n_rtlsdr == 1) && (device_index == -1)) {
    device_index = 0;
  }
  if ((device_index < 0) || (device_index >= n_rtlsdr)) {
    std::cerr
        << "Error: must specify which USB device to use with --device-index"
        << std::endl;
    std::cerr << "Found the following USB devices:" << std::endl;
    char vendor[256], product[256], serial[256];
    for (int t = 0; t < n_rtlsdr; t++) {
      rtlsdr_get_device_usb_strings(t, vendor, product, serial);
      std::cerr << "Device index " << t << ": [Vendor: " << vendor
                << "] [Product: " << product << "] [Serial#: " << serial << "]"
                << std::endl;
    }
  }

  // Open
  if (rtlsdr_open(&mDevice, device_index) < 0) {
    std::cerr << "ERROR: unable to open RTLSDR device" << std::endl;
    throw std::logic_error("Fatal Error");
  }


  if (rtlsdr_set_direct_sampling(mDevice, ElectrosenseContext::getInstance()->getDirectSamplingMode()) < 0) {
      std::cerr << "Error: unable to rtlsdr_set_direct_sampling" << std::endl;
      throw std::logic_error("Fatal Error, rtlsdr_set_direct_sampling");
  } else {
      std::cout << "direct sampling mode set properly, " << ElectrosenseContext::getInstance()->getDirectSamplingMode() << std::endl;
  }


  int samplingRate = ElectrosenseContext::getInstance()->getSamplingRate();

  // Sampling frequency
  if (rtlsdr_set_sample_rate(mDevice, samplingRate) < 0) {
    std::cerr << "ERROR: unable to set sampling rate to " << samplingRate
              << std::endl;
    throw std::logic_error("Fatal Error");
  }

  int frequency = 24e6; // default value

  if (rtlsdr_set_center_freq(mDevice, frequency) < 0) {
    std::cerr << "ERROR: unable to set frequency to" << frequency << std::endl;
    throw std::logic_error("Fatal Error");
  }

  int *gains;
  int count = rtlsdr_get_tuner_gains(mDevice, NULL);
  if (count > 0) {
    gains = (int *)malloc(sizeof(int) * count);
    count = rtlsdr_get_tuner_gains(mDevice, gains);
    std::cout << "Gain available: ";
    for (int i = 0; i < count; i++)
      std::cout << gains[i] << " , ";

    std::cout << std::endl;
    free(gains);
  }

  int gain = ElectrosenseContext::getInstance()->getGain();

  int r = rtlsdr_set_tuner_gain_mode(mDevice, 1);
  if (r < 0) {
    std::cerr << "ERROR: Failed to enable manual gain mode" << std::endl;
    throw std::logic_error("Fatal Error");
  }
  r = rtlsdr_set_tuner_gain(mDevice, gain * 10);
  if (r < 0) {
    std::cerr << "ERROR: Failed to set manual tuner gain" << std::endl;
    throw std::logic_error("Fatal Error");
  } else {
    int g = rtlsdr_get_tuner_gain(mDevice);
    std::cout << "Gain set to " << g / 10 << std::endl;
  }

  // Set bias tee
  int biasT = ElectrosenseContext::getInstance()->getBiasTee();
  std::string enabled = "";
  if (biasT == 1) {
    rtlsdr_set_bias_tee(mDevice, biasT);
    enabled = "True";
  }
  else {
    enabled = "False";
  }

  // Reset the buffer
  if (rtlsdr_reset_buffer(mDevice) < 0) {
    std::cerr << "Error: unable to reset RTLSDR buffer" << std::endl;
  }

  std::cout << "[*] Initializing dongle with following configuration: "
            << std::endl;
  std::cout << "\t Center Frequency: " << frequency << " Hz" << std::endl;
  std::cout << "\t Sampling Rate: " << samplingRate << " samples/sec"
            << std::endl;
  std::cout << "\t Gain: " << gain << " dB" << std::endl;
  std::cout << "\t Bias-T: " << enabled << std::endl;

  // Check if the converter is present

  mConverterDriver.portPath = new char[CONVERTER_PATH.size() + 1];
  std::copy(CONVERTER_PATH.begin(), CONVERTER_PATH.end(),
            mConverterDriver.portPath);
  mConverterDriver.portPath[CONVERTER_PATH.size()] = '\0';

  if (!converterInit(&mConverterDriver)) {
    std::cerr << "Warning: Failed to open the converter" << std::endl;
    // throw std::logic_error("Failed to open the converter");
  } else {
    std::cout << "Converter has been detected properly" << std::endl;
    mConverterEnabled = true;
  }

  if (! mConverterEnabled && ElectrosenseContext::getInstance()->getMinFreq() < 24e6) {
      ElectrosenseContext::getInstance()->setDirectSamplingMode(2);
      std::cout << "[INFO] Direct Sampling (mode=2) has been enabled" << std::endl;
  }

  delete[] mConverterDriver.portPath;

  return 1;
}

int rtlsdrDriver::close() { return 1; }

void timespec_diff(struct timespec *start, struct timespec *stop,
                   struct timespec *result) {
  if ((stop->tv_nsec - start->tv_nsec) < 0) {
    result->tv_sec = stop->tv_sec - start->tv_sec - 1;
    result->tv_nsec = stop->tv_nsec - start->tv_nsec + 1000000000;
  } else {
    result->tv_sec = stop->tv_sec - start->tv_sec;
    result->tv_nsec = stop->tv_nsec - start->tv_nsec;
  }

  return;
}

typedef struct {
  std::vector<std::complex<float>> *buf;
  rtlsdr_dev_t *dev;
  uint64_t center_frequency;
  long sampling_rate;
  long down_sampling;
  long chunk_size;
  long overlap_size;
  unsigned int duration;
  long *samples_read;
  struct timespec init_time;
  int init_sampling;
  int sensor_id;

  int sending_mode;  // 0: continuous | 1: interleave
  int sending_state; // 0: sampling   | 1: waiting

  int waiting_time;
  int sampling_time;
  int waiting_flow;
  int sampling_flow;

  bool converter_enable;

  ElectrosenseContext *context;

  converter *conv;

  ReaderWriterQueue<SpectrumSegment *> *queue;
  ReaderWriterQueue<SpectrumSegment *> *queue2;
} callback_package_t;

static void capbuf_rtlsdr_callback(unsigned char *buf, uint32_t len,
                                   void *ctx) {

  struct sched_param param;
  param.sched_priority = 20;
  pthread_setschedparam(pthread_self(), SCHED_FIFO, &param);

  struct timespec current_time;
  clock_gettime(CLOCK_REALTIME, &current_time);

  // Getting parameters
  callback_package_t *cp_p = (callback_package_t *)ctx;
  callback_package_t &cp = *cp_p;
  std::vector<std::complex<float>> capbuf_raw_p = *cp.buf;
  uint64_t center_freq = cp.center_frequency;
  ReaderWriterQueue<SpectrumSegment *> *queue = cp.queue;
  ReaderWriterQueue<SpectrumSegment *> *queue2 = cp.queue2;

  rtlsdr_dev_t *dev = cp.dev;
  ElectrosenseContext *esense = cp_p->context;

  // we set init time to current time only in the first execution
  if (cp.init_time.tv_sec == 0)
    cp.init_time = current_time;

  if (esense->getPipeline().compare("DEC") == 0) {

      // capbuf_raw_p.reserve(len/2);
      //  for (uint32_t t=0;t<len;t=t+2) {
      //      capbuf_raw_p.push_back( std::complex<float>(buf[t] ,buf[t+1] ));
      //  }

      // std::cout << "[*] Sending segment " << current_time.tv_sec << "." <<
      // current_time.tv_nsec << std::endl; printf("** %u , %u\n", buf[0], buf[1]);

      SpectrumSegment *segment = new SpectrumSegment(
              -1000, current_time, center_freq,
              ElectrosenseContext::getInstance()->getSamplingRate(), buf, len);

      queue->enqueue(segment);

      SpectrumSegment *segment2 = new SpectrumSegment(
              -1000, current_time, center_freq,
              ElectrosenseContext::getInstance()->getSamplingRate(), buf, len);
      queue2->enqueue(segment2);

  }
  else if (esense->getPipeline().compare("IQ") == 0) {

      SpectrumSegment *segment = new SpectrumSegment(
              -1000, current_time, center_freq,
              ElectrosenseContext::getInstance()->getSamplingRate(), buf, len);

      queue->enqueue(segment);

  } else {  // PSD PIPELINE

    capbuf_raw_p.reserve(len / 2);

    for (uint32_t t = 0; t < len; t = t + 2) {
      capbuf_raw_p.push_back(std::complex<float>(buf[t], buf[t + 1]));
    }

    SpectrumSegment *segment = new SpectrumSegment(
        -1000, current_time, center_freq,
        ElectrosenseContext::getInstance()->getSamplingRate(), capbuf_raw_p);

    queue->enqueue(segment);
  }

  capbuf_raw_p.clear();

  *cp.samples_read = *cp.samples_read + len;

  struct timespec diff;
  timespec_diff(&cp.init_time, &current_time, &diff);

  if (cp.duration != 0 && (diff.tv_sec >= cp.duration)) {
    rtlsdr_cancel_async(dev);
    pthread_exit(NULL);
  }
}


static void *aux_thread(void *arg) {

  struct timespec ref_time;

  ref_time.tv_sec = ElectrosenseContext::getInstance()->getStartTimeSampling();
  ref_time.tv_nsec = 0;

  callback_package_t *cp_p = (callback_package_t *)arg;
  callback_package_t &cp = *cp_p;

  if (ElectrosenseContext::getInstance()->getStartTimeSampling() != 0) {

    struct timespec time_diff;

    // Sleep until the absolute time is fulfilled
    struct timespec currentTime;
    clock_gettime(CLOCK_REALTIME, &currentTime);

    timespec_diff(&currentTime, &ref_time, &time_diff);

    if (time_diff.tv_sec < 0 || time_diff.tv_nsec < 0) {
      std::cerr << "[ERROR] Starting Time is in the past! " << std::endl;
      pthread_exit(NULL);
    }

    std::cout << "--- IQ Sync Sampling ---" << std::endl;
    std::cout << "CurrentTime: " << currentTime.tv_sec << "."
              << currentTime.tv_nsec << std::endl;
    std::cout << "StartTime Sampling: " << ref_time.tv_sec << "."
              << ref_time.tv_nsec << std::endl;
    std::cout << "Sleeping ... " << std::endl;
    std::cout << "--- End IQ Sync Sampling ---" << std::endl << std::endl;

    clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &ref_time, NULL);
  }

  rtlsdr_read_async(cp.dev, capbuf_rtlsdr_callback, arg, 0, 0);
  pthread_exit(NULL);
}

/*
 * This thread makes polling over the GAIN and FREQUENCY values to
 * set the receiver accordingly
 * TODO: Review the concurrence since this thread and rtlsdrDriver::run could
 * have access at the same time to the rtl device
 *
 * */
static void *socket_webrtc_thread(void *arg) {

  callback_package_t *cp_p = (callback_package_t *)arg;
  callback_package_t &cp = *cp_p;

  rtlsdr_dev_t *dev = cp.dev;
  converter *conv = cp.conv;

  ElectrosenseContext *esense = cp_p->context;

  uint64_t last_fc = esense->getMinFreq();
  uint64_t proxy_freq = 0, previous_proxy_freq = 0;

  float last_gain = esense->getGain();

  bool mustInvert;

  while (1) {

    // Gain
    float current_gain = esense->getGain();

    if (last_gain != current_gain) {

      last_gain = current_gain;

      if (current_gain > 0) {

        int r = rtlsdr_set_tuner_gain_mode(dev, 1);
        if (r < 0) {
          std::cerr << "ERROR: Failed to enable manual gain mode" << std::endl;
        } else {
          r = rtlsdr_set_tuner_gain(dev, current_gain * 10);
          if (r < 0) {
            std::cerr << "ERROR: Failed to set manual tuner gain" << std::endl;
          } else {
            int g = rtlsdr_get_tuner_gain(dev);
            std::cout << "Gain set to " << g / 10 << std::endl;
          }
        }
      } else if (current_gain == 0) {

        int r = rtlsdr_set_tuner_gain_mode(dev, 0);
        if (r < 0)
          std::cerr << "ERROR: Failed to enable automatic gain mode"
                    << std::endl;
        else
          std::cout << "Automatic Gain control enable" << std::endl;
      } else
        std::cerr << "Gain value not allowed" << current_gain << std::endl;
    }

    // Frequency

    uint64_t current_fc = esense->getMinFreq();

    if (last_fc != current_fc) {

      last_fc = current_fc;

      if (!cp.converter_enable) {

        // Native RTL-SDR
        int r = rtlsdr_set_center_freq(dev, esense->getMinFreq());
        if (r != 0)
          std::cerr << "Error: unable to set center freq: " << esense->getMinFreq() << std::endl;

      } else {
        // Converter

        if (!converterTune(conv, esense->getMinFreq() / 1e3, &proxy_freq, &mustInvert)) {
          throw std::logic_error("Failed to converterTune");
        }

        // printf("Tuning to %llu Hz, receiving on %llu kHz\n", center_freq,
        // proxy_freq);

        if (previous_proxy_freq != proxy_freq) {

          previous_proxy_freq = proxy_freq;

          int r = rtlsdr_set_center_freq(dev, proxy_freq * 1e3);
          if (r != 0) {
            std::cerr << "Error: unable to set center frequency" << std::endl;
          } else {
            std::cout << "Center Frequency: " << proxy_freq * 1e3 << std::endl;
          }
        }
      }
    }

    usleep(0.1);
  }
}

void rtlsdrDriver::run() {

  mRunning = true;

  if (ElectrosenseContext::getInstance()->getPipeline().compare("PSD") == 0) {
    std::cout << "rtlsdrDriver: SyncSampling ..... " << std::endl;
    SyncSampling();

  } else {

    // Reserving 262144 values for the buffer"
    m_capbuf_raw.reserve((256 * 1024) / 2);
    mSeqHopping = new SequentialHopping();
    long samples_read = 0;

    callback_package_t cp;
    cp.buf = &m_capbuf_raw;
    cp.center_frequency = ElectrosenseContext::getInstance()->getMinFreq();
    cp.queue = mQueueOut;
    cp.queue2 = mQueueOut2;
    cp.duration = ElectrosenseContext::getInstance()->getMonitorTime();
    cp.dev = mDevice;
    cp.converter_enable = mConverterEnabled;
    cp.conv = &mConverterDriver;

    cp.init_time.tv_sec = 0;
    cp.init_time.tv_nsec = 0;
    cp.samples_read = &samples_read;

    int r = rtlsdr_set_center_freq(mDevice, cp.center_frequency);
    if (r != 0) {
      std::cerr << "Error: unable to set center frequency" << std::endl;
      mRunning = false;
    } else {
      std::cout << "Center Frequency: " << cp.center_frequency << " Hz"
                << std::endl;
    }

    // Reset the buffer
    if (rtlsdr_reset_buffer(mDevice) < 0) {
      std::cerr << "Error: unable to reset RTLSDR buffer" << std::endl;
      mRunning = false;
    }

    cp.context = ElectrosenseContext::getInstance();

    if (ElectrosenseContext::getInstance()->getPipeline().compare("DEC") == 0) {

      printf("[rtlsdrDriver] Creating communication socket for WebRTC\n");

      pthread_t s_th;
      pthread_create(&s_th, NULL, &socket_webrtc_thread, (void *)&cp);

      // pthread_create(&threads[i], NULL, &(SVAnchor::extensionStep), &td[i]);
    }

    // Workaround for the RPI for finishing the thread properly
    pthread_t myth;
    pthread_create(&myth, NULL, aux_thread, (void *)&cp);
    pthread_join(myth, NULL);

    m_capbuf_raw.clear();

    std::cout << "[*] rtlsdrDriver: samples read: " << *cp.samples_read
              << std::endl;
  }

  mRunning = false;
}

void rtlsdrDriver::SyncSampling() {

  const int BULK_TRANSFER_MULTIPLE = 512;

  std::cout << "rtlsdrDriver::run" << std::endl;

  mSeqHopping = new SequentialHopping();
  uint64_t center_freq = 0, previous_freq = 0, fft_size = 0, slen = 0;
  uint64_t proxy_freq = 0, previous_proxy_freq = 0;
  bool mustInvert;

  uint8_t *iq_buf = NULL;
  bool direct_sampling = true;
  bool exchange = false;
  bool copy_1freq = true;
  bool copy_2freq= true;
  int count = 0;



//--------------------------------------------------------------------------------------------------------
// HOP_OLD (part 1 of 2)
//---------------------
/*
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(900000000, 1000000000);
    double n = dist(mt);
    std::uniform_real_distribution<double> dist2(30, 50);
*/
//----------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------
// NOISE / HOP / SPOOF  Initiation (part 1 of 2)
//---------------------

//    std::uniform_real_distribution<double> dist(0, 10);
//    std::random_device urandom("/dev/urandom");

//-------------------------------------------------------------------------------



  while (mRunning) {

    // Introduce here the concept of segment per band (before jumping).

    center_freq = mSeqHopping->nextHop();
    mustInvert = false;

    if (previous_freq != center_freq) {
      previous_freq = center_freq;

      // RTL-SDR as proxy of the down-converter
      if (mConverterEnabled) {

        if (!converterTune(&mConverterDriver, center_freq / 1e3, &proxy_freq,
                           &mustInvert)) {
          mRunning = false;
          throw std::logic_error("Failed to converterTune");
        }
         // printf("Tuning to %llu Hz, receiving on %llu kHz\n", center_freq,
        // proxy_freq);

        if (previous_proxy_freq != proxy_freq) {

          previous_proxy_freq = proxy_freq;

          int r = rtlsdr_set_center_freq(mDevice, proxy_freq * 1e3);
          if (r != 0) {
            std::cerr << "Error: unable to set center frequency: "<< proxy_freq * 1e3 << std::endl;
            continue;
          }

          // Reset the buffer
          if (rtlsdr_reset_buffer(mDevice) < 0) {
            std::cerr << "Error: unable to reset RTLSDR buffer" << std::endl;
            mRunning = false;
          }
        }

      // Native RTL-SDR
      } else {

          // Direct sampling
          if (ElectrosenseContext::getInstance()->getDirectSamplingMode() > 0) {
              if (center_freq >= 24e6 && direct_sampling) {

                  if (rtlsdr_set_direct_sampling(mDevice, 0) < 0) {
                      std::cerr << "Error: unable to disable direct_sampling" << std::endl;
                      throw std::logic_error("Fatal Error, unable to disable direct_sampling");
                  }

                  int gain = ElectrosenseContext::getInstance()->getGain();
                  rtlsdr_set_agc_mode(mDevice, 0);
                  int r = rtlsdr_set_tuner_gain_mode(mDevice, 1);
                  if (r < 0) {
                      std::cerr << "ERROR: Failed to enable manual gain mode" << std::endl;
                      throw std::logic_error("Fatal Error");
                  }
                  r = rtlsdr_set_tuner_gain(mDevice, gain * 10);
                  if (r < 0) {
                      std::cerr << "ERROR: Failed to set manual tuner gain" << std::endl;
                      throw std::logic_error("Fatal Error");
                  } else {
                      int g = rtlsdr_get_tuner_gain(mDevice);
                      std::cout << "Gain set to " << g / 10 << std::endl;
                  }


                  direct_sampling = false;

              } else if (center_freq < 24e6 && !direct_sampling) {


                  if (rtlsdr_set_direct_sampling(mDevice, 2) < 0) {
                      std::cerr << "Error: unable to set direct_sampling" << std::endl;
                      throw std::logic_error("Fatal Error, unable to set direct_sampling");
                  }
                  rtlsdr_set_tuner_gain_mode(mDevice, 0);
                  rtlsdr_set_agc_mode(mDevice, 1);
                  direct_sampling = true;
              }
          }

        int r = rtlsdr_set_center_freq(mDevice, center_freq);
        if (r != 0) {
          std::cerr << "Error: unable to set center frequency: " << center_freq << std::endl;
          continue;
        }

        // Reset the buffer
        if (rtlsdr_reset_buffer(mDevice) < 0) {
          std::cerr << "Error: unable to reset RTLSDR buffer" << std::endl;
          mRunning = false;
        }
      }
    }

    unsigned int current_fft_size =
        1 << ElectrosenseContext::getInstance()->getLog2FftSize();

    if (fft_size != current_fft_size) {

      fft_size = current_fft_size;

      slen = ((current_fft_size -
               ElectrosenseContext::getInstance()->getSoverlap()) *
                  ElectrosenseContext::getInstance()->getAvgFactor() +
              ElectrosenseContext::getInstance()->getSoverlap()) * 2;

      // NOTE: libusb_bulk_transfer for RTL-SDR seems to crash when not reading
      // multiples of 512 (BULK_TRANSFER_MULTIPLE)
      if (slen % BULK_TRANSFER_MULTIPLE != 0)
        slen = slen + (BULK_TRANSFER_MULTIPLE - (slen % BULK_TRANSFER_MULTIPLE));

      iq_buf = (uint8_t *)realloc(iq_buf, slen * sizeof(uint8_t));
    }

    int n_read;
    struct timespec current_time;
    clock_gettime(CLOCK_REALTIME, &current_time);

    int r = rtlsdr_read_sync(mDevice, iq_buf, slen, &n_read);
    if (r != 0 || (unsigned int)n_read != slen) {
      fprintf(stderr, "WARNING: Synchronous read failed.\n");
      mRunning = false;
    }

    if (mustInvert) {
      for (int i = 0; i < n_read; i += 2) {
        iq_buf[i] = 255 - iq_buf[i];
      }
    }

    std::vector<std::complex<float>> iq_vector;


//----------------------------------
//---------------------
// NO ATTACK
//---------------------
//-----------------------------------

    for (unsigned int i = 0; i < ElectrosenseContext::getInstance()->getAvgFactor(); i++) {
      iq_vector.clear();


      //if((center_freq >= 80000000 ) && (center_freq <= 82000000)){
	//std::cout << "CurrentTime: " << current_time.tv_sec << "." << current_time.tv_nsec << std::endl;
      //}


      for (unsigned int j = 0; j < current_fft_size * 2; j = j + 2) {

        // Every segment overlaps getSoverlap() samples in time domain.
          iq_vector.push_back(std::complex<float>(
            iq_buf[j + i * (current_fft_size - ElectrosenseContext::getInstance()->getSoverlap()) * 2],
            iq_buf[j + 1 + i * (current_fft_size - ElectrosenseContext::getInstance()->getSoverlap()) * 2]));
        }

//---------------------------------------------------------------------------------------------------




//-----------------------------------------------------------------------------------------------------
// HOP_OLD - LEFT TO IMPLEMENT WALKIE TALKIE BEHAVIOR
//-------------------
/*

    for (unsigned int i = 0; i < ElectrosenseContext::getInstance()->getAvgFactor(); i++) {
      iq_vector.clear();

      //Potential way to recalculate
      if((center_freq >= 100000000) && (center_freq)<=102000000)
        n = dist(mt);

      maximum = center_freq + 2000000;

      if((center_freq <= n) && (maximum >= n)){
        for (unsigned int j = 0; j < current_fft_size * 2; j = j + 2) {
          double randomValue = dist2(mt);
          iq_vector.push_back(std::complex<float>(
             iq_buf[j + i * (current_fft_size - ElectrosenseContext::getInstance()->getSoverlap()) * 2] + randomValue,
             iq_buf[j + 1 + i * (current_fft_size - ElectrosenseContext::getInstance()->getSoverlap()) * 2] + randomValue));
        }
      }else{
          for (unsigned int j = 0; j < current_fft_size * 2; j = j + 2) {
            iq_vector.push_back(std::complex<float>(
              iq_buf[j + i * (current_fft_size - ElectrosenseContext::getInstance()->getSoverlap()) * 2],
              iq_buf[j + 1 + i * (current_fft_size - ElectrosenseContext::getInstance()->getSoverlap()) * 2]));
          }
        }

*/
//-------------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------------------
// DISORDER (EXCHANGE)
//--------------------
/*


    for (unsigned int i = 0; i < ElectrosenseContext::getInstance()->getAvgFactor(); i++) {
      iq_vector.clear();
      for (unsigned int j = 0; j < current_fft_size * 2; j = j + 2) {

        iq_vector.push_back(std::complex<float>(
          iq_buf[j + i * (current_fft_size - ElectrosenseContext::getInstance()->getSoverlap()) * 2],
          iq_buf[j + 1 + i * (current_fft_size - ElectrosenseContext::getInstance()->getSoverlap()) * 2]));
      }

      std::string data;
      std::complex<float> f;
      //std::vector<std::complex<float>> aux;

      if (!exchange && center_freq > 300000000 && center_freq < 301000000) {
	 //Create folders if they do not exists
         std::string root_folder_name ="/root/disorder/";
         mkdir(root_folder_name.c_str(), 0777);

	 std::ofstream file_write_1 ("/root/disorder/copy_vector_1.txt");
	 std::ofstream file_write_2 ("/root/disorder/copy_vector_2.txt");
         for(unsigned int i = 0; i < iq_vector.size(); i++){
           file_write_1 << iq_vector[i] << std::endl;
	   file_write_2 << iq_vector[i] << std::endl;
         }
         file_write_1.close();
	 file_write_2.close();
	 exchange = true;
      }
      else{
        if (exchange && (center_freq > 90000000 && center_freq < 91000000)){
	  if (copy_1freq){

	    // Copy in file 1 the content of Iq_vector
	    std::ofstream file_write_1 ("/root/disorder/copy_vector_1.txt");
            for(unsigned int i = 0; i < iq_vector.size(); i++){
              file_write_1 << iq_vector[i] << std::endl;
            }
	    file_write_1.close();

	    // Copy in  Iq_vector the content of file 2
	    std::ifstream file_2 ("/root/disorder/copy_vector_2.txt");
            iq_vector.clear();
            while (!file_2.eof()) {
              file_2 >> data;
              std::istringstream is(data);
              is>>f;
              iq_vector.push_back(f);
            }
            file_2.close();
	    copy_1freq = false;

	  }else{
            // Copy in  Iq_vector the content of file 2
	    std::ifstream file_2 ("/root/disorder/copy_vector_2.txt");
	    iq_vector.clear();
            while (!file_2.eof()) {
              file_2 >> data;
              std::istringstream is(data);
              is>>f;
              iq_vector.push_back(f);
            }
            file_2.close();
	    copy_2freq = true;
	  }
        }
        if (exchange && (center_freq > 300000000 && center_freq < 301000000)){
          if (copy_2freq){
	    // Copy in file 2 the content of iq_vector
	    std::ofstream file_write_2 ("/root/disorder/copy_vector_2.txt");
            for(unsigned int i = 0; i < iq_vector.size(); i++){
              file_write_2 << iq_vector[i] << std::endl;
            }
	    file_write_2.close();

	    // Copy in iq_vector the content of file 1
	    std::ifstream file_1 ("/root/disorder/copy_vector_1.txt");
	    iq_vector.clear();
            while (!file_1.eof()) {
              file_1 >> data;
              std::istringstream is(data);
              is>>f;
              iq_vector.push_back(f);
            }
            file_1.close();
            copy_2freq = false;
          }else{
            //Copy in iq_vector the content of file 1
 	    std::ifstream file_1 ("/root/disorder/copy_vector_1.txt");
            iq_vector.clear();
            while (!file_1.eof()) {
              file_1 >> data;
              std::istringstream is(data);
              is>>f;
              iq_vector.push_back(f);
            }
            file_1.close();
	    copy_1freq = true;
          }
        }
      }

*/
//---------------------------------------------------------------------------------------------------------------




//-------------------------------------------------------------------------------------------------------------
// PSEUDO - NOISE (not detectable)
//---------------------
/*

    for (unsigned int i = 0; i < ElectrosenseContext::getInstance()->getAvgFactor(); i++) {
      iq_vector.clear();
      for (unsigned int j = 0; j < current_fft_size * 2; j = j + 2) {

        float random = 10 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(20/10)));

        iq_vector.push_back(std::complex<float>(
            iq_buf[j + i * (current_fft_size - ElectrosenseContext::getInstance()->getSoverlap()) * 2] + random,
            iq_buf[j + 1 + i * (current_fft_size - ElectrosenseContext::getInstance()->getSoverlap()) * 2] + random));
      }

*/
//----------------------------------------------------------------------------------------------------------------




//-------------------------------------------------------------------------------------------------------------
//  REPEAT - Modifies Spectrum Segments with the the PSD values of one of them
//--------------------------------------------------------------------
/*
    for (unsigned int i = 0; i < ElectrosenseContext::getInstance()->getAvgFactor(); i++) {
      iq_vector.clear();
      for (unsigned int j = 0; j < current_fft_size * 2; j = j + 2) {
        iq_vector.push_back(std::complex<float>(
          iq_buf[j + i * (current_fft_size - ElectrosenseContext::getInstance()->getSoverlap()) * 2],
          iq_buf[j + 1 + i * (current_fft_size - ElectrosenseContext::getInstance()->getSoverlap()) * 2]));
      }

      std::string data;
      std::complex<float> f;

      //-- Indicates the frequency segment affected by the attack
      if (center_freq >= 400000000 && center_freq <= 480000000) {

        //--Create the temporary vector
         std::vector<std::complex<float>> source_segment;


        //-- If the vector with the PSD values already exists, it copies its content to the segment to be sent
        if (!source_segment.empty()) {
          iq_vector.clear();
          for(unsigned int i = 0; i < source_segment.size(); i++) {
            iq_vector.push_back(source_segment[i]);
          }
        }

        //-- If the vector is empty it creates it and saves the PSD values of the selected frequency segment
        else {
          for(unsigned int i = 0; i < iq_vector.size(); i++) {
            source_segment.push_back(iq_vector[i]);
          }
        }
     }

*/
//----------------------------------------------------------------------------------------------------------




//-------------------------------------------------------------------------------------------------------------
// DELAY -
//-------------------------------------------------------------------
/*

    for (unsigned int i = 0; i < ElectrosenseContext::getInstance()->getAvgFactor(); i++) {

      iq_vector.clear();
      for (unsigned int j = 0; j < current_fft_size * 2; j = j + 2) {
        iq_vector.push_back(std::complex<float>(
          iq_buf[j + i * (current_fft_size - ElectrosenseContext::getInstance()->getSoverlap()) * 2],
          iq_buf[j + 1 + i * (current_fft_size - ElectrosenseContext::getInstance()->getSoverlap()) * 2]));
      }


      if(center_freq > 80000000 && center_freq < 81000000){
	//Create folders if they do not exists
        std::string root_folder_name ="/root/delay/";
        mkdir(root_folder_name.c_str(), 0777);
        std::string segment_folder_name ="/root/delay/"+std::to_string(center_freq);
	const char* dirname = segment_folder_name.c_str();
        mkdir(dirname, 0777);

	//Generate the name of the files saving the PSD of each RF Segment
	count = 0;
        std::string filename ="/root/delay/"+std::to_string(center_freq)+"/"+std::to_string(current_time.tv_sec)+"_"+std::to_string(count)+".txt";
        std::ifstream f (filename);
        bool exist = f.good();

        while (exist){
          count = count + 1;
          filename ="/root/delay/"+std::to_string(center_freq)+"/"+std::to_string(current_time.tv_sec)+"_"+std::to_string(count)+".txt";
          std::ifstream f (filename);
	  exist = f.good();
	}

        //Creates the file and saves the PSD values of the segment
	std::ofstream file (filename);
        for(unsigned int i = 0; i < iq_vector.size(); i++) {
          file << iq_vector[i] << std::endl;
        }
        file.close();
	//std::cout <<"+Create new file :" <<filename << std::endl;


 	//Copies the PSD values of the oldest file in the iq_vector and delets the files
        int time = current_time.tv_sec - 0000000100;
        std::string str;
	std::vector<std::string> files;
	int num;
        DIR *dr;
        struct dirent *en;

        dr = opendir(segment_folder_name.c_str()); //open all directory
	if (dr) {
          while ((en = readdir(dr)) != NULL) {
            str = en->d_name;
	    //std::cout<<str<<" ";
	    if (str != "." && str != ".."){
		files.push_back(str);
	    }
	  }
	  std::sort(files.begin(), files.end());
	  for (const std::string &s_aux:files){
	      str = s_aux;
	      //std::cout << "str: " << str << std::endl;
	      str = str.substr(0,10);
              std::stringstream ss;
	      ss << str;
              ss >> num;
	      //std::string var (en->d_name);
       	      //std::cout<<str<<" ";
              //std::cout<<num<<" "<<std::endl;
	      //std::cout <<"file Name: " << var << " File time: " << num << " time to delete: "<< time <<std::endl;
	      if ((num < time)){
	        //std::cout << "Old File found: " << en->d_name << std::endl;
	        filename = "/root/delay/"+std::to_string(center_freq)+"/"+s_aux;
	        //std::cout <<"=Copy from Old file to vector :" <<filename << std::endl;
	        std::ifstream file (filename);
	        //std::cout<<filename<<std::endl;
                if (file.good()) {
                  iq_vector.clear();
                  while (!file.eof()) {
                    std::complex<float> f_f;
	            std::string data;
		    file >> data;
                    std::istringstream is(data);
                    is >> f_f;
                    iq_vector.push_back(f_f);
                  }
                  file.close();
		  //std::cout << "Delete: " << filename <<std::endl;
	          remove(filename.c_str());
		  break;
                }
	      }
          }
          closedir(dr); //close all directory
        }
      }

*/
//--------------------------------------------------------------------------------------------------------




//----------------------------------------------------------------------------------------------------------
// FREEZE - Modifies the PSD values of each Spectrum Segment with a previous version of each Segment
//---------------------------------------------
/* To repair

    for (unsigned int i = 0; i < ElectrosenseContext::getInstance()->getAvgFactor(); i++) {
      iq_vector.clear();
      for (unsigned int j = 0; j < current_fft_size * 2; j = j + 2) {
        iq_vector.push_back(std::complex<float>(
          iq_buf[j + i * (current_fft_size - ElectrosenseContext::getInstance()->getSoverlap()) * 2],
          iq_buf[j + 1 + i * (current_fft_size - ElectrosenseContext::getInstance()->getSoverlap()) * 2]));
      }

      std::string data;
      std::complex<float> f;
      std::string filename;

      if ((center_freq >= 200000000) && (center_freq <= 360000000)){

        //Create folders if they do not exists
        std::string root_folder_name ="/root/freeze/";
        mkdir(root_folder_name.c_str(), 0777);


        //Generate the name of the files saving the PSD of each RF Segment
        count = 0;
        std::string filename ="/root/freeze/"+ std::to_string(center_freq)+"_"+std::to_string(count)+".txt";
        std::ifstream file (filename);
        bool exist = file.good();

        while (exist){
          count = count + 1;
          filename ="/root/freeze/"+ std::to_string(center_freq)+"_"+std::to_string(count)+".txt";
          std::ifstream file (filename);
          exist = file.good();
        }


	if (!file.good() && count <= 5) {
          //Creates the file and saves the PSD values of the segment
          std::ofstream file1 (filename);
          for(unsigned int i = 0; i < iq_vector.size(); i++) {
            file1 << iq_vector[i] << std::endl;
          }
          file1.close();
          //std::cout <<"+Create new file :" <<filename << std::endl;
	}
	else {
	  std::ifstream file2 (filename);
          iq_vector.clear();
          while (!file2.eof()) {
            file2 >> data;
            std::istringstream is(data);
            is >> f;
            iq_vector.push_back(f);
          }
          file2.close();
        }
      }

*/
//----------------------------------------------------------------------------------------------------------




//--------------------------------------------------------------------------------------------------------------
// HOP  part 2 of 2 - Modifies some PSD values (randomly selected) of Spectrum Segments  adding random noise
//------------------------------------
/*

    for (unsigned int i = 0; i < ElectrosenseContext::getInstance()->getAvgFactor(); i++) {
      iq_vector.clear();
      if((center_freq >= 300000000) && (center_freq <= 301000000)){
        for (unsigned int j = 0; j < current_fft_size * 2; j = j + 2) {
	  double randomValue = dist(urandom);
          //double randomValue = dist(mt);
 	  if (randomValue > 5){
            iq_vector.push_back(std::complex<float>(
               iq_buf[j + i * (current_fft_size - ElectrosenseContext::getInstance()->getSoverlap()) * 2] + randomValue,
               iq_buf[j + 1 + i * (current_fft_size - ElectrosenseContext::getInstance()->getSoverlap()) * 2] + randomValue));
          }
          else {
            iq_vector.push_back(std::complex<float>(
               iq_buf[j + i * (current_fft_size - ElectrosenseContext::getInstance()->getSoverlap()) * 2],
               iq_buf[j + 1 + i * (current_fft_size - ElectrosenseContext::getInstance()->getSoverlap()) * 2]));
	  }
        }
      }
      else{
        for (unsigned int j = 0; j < current_fft_size * 2; j = j + 2) {
	  iq_vector.push_back(std::complex<float>(
             iq_buf[j + i * (current_fft_size - ElectrosenseContext::getInstance()->getSoverlap()) * 2],
             iq_buf[j + 1 + i * (current_fft_size - ElectrosenseContext::getInstance()->getSoverlap()) * 2]));
        }
      }

*/
//---------------------------------------------------------------------------------------------------------




//----------------------------------------------------------------------------------------------------------
//  MIMIC - Copies one band in another band
//---------------------------------------
/*

    for (unsigned int i = 0; i < ElectrosenseContext::getInstance()->getAvgFactor(); i++) {
      iq_vector.clear();
      for (unsigned int j = 0; j < current_fft_size * 2; j = j + 2) {
        iq_vector.push_back(std::complex<float>(
          iq_buf[j + i * (current_fft_size - ElectrosenseContext::getInstance()->getSoverlap()) * 2],
          iq_buf[j + 1 + i * (current_fft_size - ElectrosenseContext::getInstance()->getSoverlap()) * 2]));
      }

      std::string data;
      std::complex<float> f;

      if (center_freq > 90000000 && center_freq < 91000000 ) {
        //Create folders if they do not exists
        std::string root_folder_name ="/root/mimic/";
        mkdir(root_folder_name.c_str(), 0777);

	std::ofstream file_write_1 ("/root/mimic/vector.txt");
        for(unsigned int i = 0; i < iq_vector.size(); i++){
          file_write_1 << iq_vector[i] << std::endl;
        }
        file_write_1.close();
      }
      else if (center_freq > 300000000 && center_freq < 301000000) {
        // Copy in  Iq_vector the content of file 2
        std::ifstream file_2 ("/root/mimic/vector.txt");
        iq_vector.clear();
        while (!file_2.eof()) {
          file_2 >> data;
          std::istringstream is(data);
          is>>f;
          iq_vector.push_back(f);
        }
        file_2.close();
        copy_1freq = false;
      }
*/
//------------------------------------------------------------------------------------------------------





//----------------------------------------------------------------------------------------------------------
// SPOOF part 2 of 2 - Copies one band in another and add random noise
//---------------------------------------
/*

    for (unsigned int i = 0; i < ElectrosenseContext::getInstance()->getAvgFactor(); i++) {
      iq_vector.clear();
      for (unsigned int j = 0; j < current_fft_size * 2; j = j + 2) {
        iq_vector.push_back(std::complex<float>(
          iq_buf[j + i * (current_fft_size - ElectrosenseContext::getInstance()->getSoverlap()) * 2],
          iq_buf[j + 1 + i * (current_fft_size - ElectrosenseContext::getInstance()->getSoverlap()) * 2]));
      }

      std::string data;
      std::complex<float> f;

      if (center_freq > 80000000 && center_freq < 81000000 ) {

        //Create folders if they do not exists
        std::string root_folder_name ="/root/spoof/";
        mkdir(root_folder_name.c_str(), 0777);

	std::ofstream file_write_1 ("/root/spoof/vector.txt");
        for(unsigned int i = 0; i < iq_vector.size(); i++){
          file_write_1 << iq_vector[i] << std::endl;
        }
        file_write_1.close();
      }
      else if (center_freq > 200000000 && center_freq < 201000000) {

        std::ifstream file_2 ("/root/spoof/vector.txt");
        iq_vector.clear();
        while (!file_2.eof()) {
          std::complex<float> randomValue = dist(urandom);
          file_2 >> data;
          std::istringstream is(data);
          is>>f;
          f = f + randomValue;
          iq_vector.push_back(f);
        }
        file_2.close();
        copy_1freq = false;
      }

*/
//-------------------------------------------------------------------------------------------------------





//----------------------------------------------------------------------------------------------------------
// NOISE 2 of 2 - Adds random noise to PSD values of Spectrum segments
//--------------------
/*

    for (unsigned int i = 0; i < ElectrosenseContext::getInstance()->getAvgFactor(); i++) {
      iq_vector.clear();
      if((center_freq >= 400000000) && (center_freq <= 420000000)){
        for (unsigned int j = 0; j < current_fft_size * 2; j = j + 2) {
          double randomValue = dist(urandom);
          iq_vector.push_back(std::complex<float>(
             iq_buf[j + i * (current_fft_size - ElectrosenseContext::getInstance()->getSoverlap()) * 2] + randomValue,
             iq_buf[j + 1 + i * (current_fft_size - ElectrosenseContext::getInstance()->getSoverlap()) * 2] + randomValue));
        }
      }else{
        for (unsigned int j = 0; j < current_fft_size * 2; j = j + 2) {
          iq_vector.push_back(std::complex<float>(
            iq_buf[j + i * (current_fft_size - ElectrosenseContext::getInstance()->getSoverlap()) * 2],
            iq_buf[j + 1 + i * (current_fft_size - ElectrosenseContext::getInstance()->getSoverlap()) * 2]));
        }
      }

*/
//---------------------------------------------------------------------------------------------------------



      // TODO: Id should be the ethernet MAC
      //std::cout<<"before creation"<<std::endl;
      SpectrumSegment *segment = new SpectrumSegment(
          -1000, current_time, center_freq, ElectrosenseContext::getInstance()->getSamplingRate(), iq_vector);
      mQueueOut->enqueue(segment);

    }
    // Last check to see if
  //   struct timespec tdiff;

  //   timespec_diff(&tinit, &current_time, &tdiff);

  //   if (duration != 0 && (tdiff.tv_sec >= duration)) {
  //     break;
  //   }
  }

  delete (mSeqHopping);
}

int rtlsdrDriver::stop() {
  mRunning = false;

  if (ElectrosenseContext::getInstance()->getPipeline().compare("PSD") == 0) {
    waitForThread();
    rtlsdr_close(mDevice);
    mDevice = NULL;

  } else  { // IQ or DEC mode
    rtlsdr_cancel_async(mDevice);
    waitForThread();
    mDevice = NULL;
  }

  return 1;
}

} // namespace electrosense