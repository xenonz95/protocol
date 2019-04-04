//
// Created by root on 18-10-16.
//

#ifndef PROTOCOL_RAWDATA_H
#define PROTOCOL_RAWDATA_H


#include <cstdint>
#include <string>

void getData(int num, uint8_t* data_holder);
void sendData(uint8_t* data, int num);

void change_endpoint(int end, std::string s = "ttyACM0");

#endif //PROTOCOL_RAWDATA_H
