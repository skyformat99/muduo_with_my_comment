// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//
// This is an internal header file, you should not include this.

#ifndef MUDUO_NET_SOCKET_H
#define MUDUO_NET_SOCKET_H

#include <boost/noncopyable.hpp>

namespace muduo
{
///
/// TCP networking.
///
namespace net
{

class InetAddress;

///
/// Wrapper of socket file descriptor.
///
/// It closes the sockfd when desctructs.
/// It's thread safe, all operations are delagated to OS.
class Socket : boost::noncopyable
{
 public:
  explicit Socket(int sockfd)
    : sockfd_(sockfd)
  { }

  // Socket(Socket&&) // move constructor in C++11
  ~Socket();

	//�����ļ�������
  int fd() const { return sockfd_; }

  /// abort if address in use
  //�൱�ڵ���bind()����
  void bindAddress(const InetAddress& localaddr);

  /// abort if address in use
	//���׽��ֱ�Ϊ�����׽���,�൱�ڵ���listen() c����
  void listen();

  /// On success, returns a non-negative integer that is
  /// a descriptor for the accepted socket, which has been
  /// set to non-blocking and close-on-exec. *peeraddr is assigned.
  /// On error, -1 is returned, and *peeraddr is untouched.
  
  //�������ӣ��൱�ڵ���accept() c����
  //peeraddr �Է��ĵ�ַ��Ϣ��ip �� �˿ں�
  int accept(InetAddress* peeraddr);

  void shutdownWrite();

//�����׽��ֵ�һЩ���� 
  ///
  /// Enable/disable TCP_NODELAY (disable/enable Nagle's algorithm).
  ///
  void setTcpNoDelay(bool on);

  ///
  /// Enable/disable SO_REUSEADDR
  ///
  void setReuseAddr(bool on);

  ///
  /// Enable/disable SO_KEEPALIVE
  ///
  void setKeepAlive(bool on);

 private:
 	//�ļ�������
  const int sockfd_;
};

}
}
#endif  // MUDUO_NET_SOCKET_H