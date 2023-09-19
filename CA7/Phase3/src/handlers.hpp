#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "../server/server.hpp"
#include "UTRIP.hpp"
#include "User.hpp"
#include <sstream>
#include <iostream>

class RandomNumberHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class HomeHandler : public RequestHandler {
private:
  UTRIP* utrip;

public:
  HomeHandler(UTRIP* utrip_)
  {
    utrip = utrip_;
  }

  Response *callback(Request *);
};

class HotelDetailsHandler : public RequestHandler
{
private:
  UTRIP* utrip;

public:
  HotelDetailsHandler(UTRIP* utrip_)
  {
    utrip = utrip_;
  }

  Response *callback(Request *);
};

class SignupHandler : public RequestHandler {
private:
  UTRIP* utrip;

public:
  SignupHandler(UTRIP* utrip_)
  {
    utrip = utrip_;
  }

  Response *callback(Request *);
};

class LoginHandler : public RequestHandler {
private:
  UTRIP* utrip;

public:
  LoginHandler(UTRIP* utrip_)
  {
    utrip = utrip_;
  }

  Response *callback(Request *);
};

class LogoutHandler : public RequestHandler {
private:
  UTRIP* utrip;

public:
  LogoutHandler(UTRIP* utrip_)
  {
    utrip = utrip_;
  }

  Response *callback(Request *);
};

class EditAccount : public RequestHandler
{
private:
  UTRIP* utrip;

public:
  EditAccount(UTRIP* utrip_)
  {
    utrip = utrip_;
  }

  Response *callback(Request *);
};

class UpdateAccount : public RequestHandler
{
private:
  UTRIP* utrip;

public:
  UpdateAccount(UTRIP* utrip_)
  {
    utrip = utrip_;
  }

  Response *callback(Request *);
};

class FilterHandler : public RequestHandler
{
private:
  UTRIP* utrip;

public:
  FilterHandler(UTRIP* utrip_)
  {
    utrip = utrip_;
  }

  Response *callback(Request *);
};

#endif
