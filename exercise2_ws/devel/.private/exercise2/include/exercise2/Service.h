// Generated by gencpp from file exercise2/Service.msg
// DO NOT EDIT!


#ifndef EXERCISE2_MESSAGE_SERVICE_H
#define EXERCISE2_MESSAGE_SERVICE_H

#include <ros/service_traits.h>


#include <exercise2/ServiceRequest.h>
#include <exercise2/ServiceResponse.h>


namespace exercise2
{

struct Service
{

typedef ServiceRequest Request;
typedef ServiceResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct Service
} // namespace exercise2


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::exercise2::Service > {
  static const char* value()
  {
    return "9671e58bec85efbba1923ae558a87802";
  }

  static const char* value(const ::exercise2::Service&) { return value(); }
};

template<>
struct DataType< ::exercise2::Service > {
  static const char* value()
  {
    return "exercise2/Service";
  }

  static const char* value(const ::exercise2::Service&) { return value(); }
};


// service_traits::MD5Sum< ::exercise2::ServiceRequest> should match
// service_traits::MD5Sum< ::exercise2::Service >
template<>
struct MD5Sum< ::exercise2::ServiceRequest>
{
  static const char* value()
  {
    return MD5Sum< ::exercise2::Service >::value();
  }
  static const char* value(const ::exercise2::ServiceRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::exercise2::ServiceRequest> should match
// service_traits::DataType< ::exercise2::Service >
template<>
struct DataType< ::exercise2::ServiceRequest>
{
  static const char* value()
  {
    return DataType< ::exercise2::Service >::value();
  }
  static const char* value(const ::exercise2::ServiceRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::exercise2::ServiceResponse> should match
// service_traits::MD5Sum< ::exercise2::Service >
template<>
struct MD5Sum< ::exercise2::ServiceResponse>
{
  static const char* value()
  {
    return MD5Sum< ::exercise2::Service >::value();
  }
  static const char* value(const ::exercise2::ServiceResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::exercise2::ServiceResponse> should match
// service_traits::DataType< ::exercise2::Service >
template<>
struct DataType< ::exercise2::ServiceResponse>
{
  static const char* value()
  {
    return DataType< ::exercise2::Service >::value();
  }
  static const char* value(const ::exercise2::ServiceResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // EXERCISE2_MESSAGE_SERVICE_H
