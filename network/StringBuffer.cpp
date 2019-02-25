//
// Created by chuli on 2019/2/24.
//

#include "StringBuffer.h"

StringBuffer::StringBuffer() {

}

StringBuffer::~StringBuffer() {

}

const char* StringBuffer::peek() {
    return _buf.c_str();
}

int StringBuffer::readableBytes() {
    return _buf.size();
}

void StringBuffer::append(const string &str) {
    _buf.append(data);
}

void StringBuffer::retrieve(int len) {
    _buf = _buf.substr(len, readableBytes());
}

string StringBuffer::retrieveAsString() {
    string result(peek(),readableBytes());
    retrieve(readableBytes());
    return result;
}