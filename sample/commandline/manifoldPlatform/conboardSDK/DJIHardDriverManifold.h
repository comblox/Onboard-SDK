#ifndef __DJIHARDDRIVERMANIFOLD_H__
#define __DJIHARDDRIVERMANIFOLD_H__


#include <stdio.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/time.h>
#include <DJI_Type.h>
#include <DJI_HardDriver.h>

namespace DJI {

namespace onboardSDK {

class HardDriverManifold : public HardDriver {

    public:
        HardDriverManifold(std::string device, unsigned int baudrate);
        ~HardDriverManifold();

        void init();

        /**
         * @brief Implement a USB hand-shaking protocol for SDK
         */
        void usbHandshake(std::string device);

        void setBaudrate(unsigned int baudrate);
        void setDevice(std::string device);

        time_t getTimeStamp();

        size_t send(const uint8_t *buf, size_t len);
        size_t readall(uint8_t *buf, size_t maxlen);

        void lockMemory();
        void freeMemory();
        void lockMSG();
        void freeMSG();

    private:
        std::string m_device;
        unsigned int m_baudrate;
        pthread_mutex_t m_memLock;
        pthread_mutex_t m_msgLock;

        int m_serial_fd;
        fd_set m_serial_fd_set;


        bool _serialOpen(const char* dev);
        bool _serialClose();
        bool _serialFlush();
        bool _serialConfig(int baudrate, char data_bits, char parity_bits, char stop_bits);

        int _serialStart(const char *dev_name, int baud_rate);
        int _serialWrite(const unsigned char *buf, int len);
        int _serialRead(unsigned char *buf, int len);

};

}

}


#endif
