//
// Created by chuli on 2019/2/24.
//

#ifndef NETWORK_STRINGBUFFER_H
#define NETWORK_STRINGBUFFER_H


class StringBuffer
{
public:
    StringBuffer();

    ~StringBuffer();

    //functions
    // append the str to this stringbuffer
    void append(const string &str);

    //retrieve the string to the len posi, called after write
    void retrieve(int len);

    //retrieve all the string, called after write
    string retrieveAsString();

    const char *peek();

    int readableBytes();

private:
    string _buf;

};


#endif //NETWORK_STRINGBUFFER_H
