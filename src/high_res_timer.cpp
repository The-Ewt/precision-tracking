/*
 * high_res_timer.cpp
 *
 *      Author: Alex Teichman
 *
 */


#include <precision_tracking/high_res_timer.h>

namespace precision_tracking {

HighResTimer::HighResTimer(const std::string& description)
  : description_(description),
    total_us_(0),
    start_(0),
	end_(0)
{
	frequency = cv::getTickFrequency();
}

void HighResTimer::start()
{
	start_ = end_ = cv::getTickCount();
}

void HighResTimer::stop()
{
	end_ = cv::getTickCount();
}

void HighResTimer::reset(const std::string& description)
{
  description_ = description;
  total_us_ = 0;
}

void HighResTimer::reset()
{
  total_us_ = 0;
}

double HighResTimer::getMicroseconds() const
{
  return total_us_;
}

double HighResTimer::getMilliseconds() const
{
  return getMicroseconds() / 1000.;
}

double HighResTimer::getSeconds() const
{
  return getMilliseconds() / 1000.;
}

double HighResTimer::getMinutes() const
{
  return getSeconds() / 60.;
}

double HighResTimer::getHours() const
{
  return getMinutes() / 60.;
}

std::string HighResTimer::reportMicroseconds() const
{
  std::ostringstream oss; oss << description_ << ": " << getMicroseconds() << " microseconds.";
  return oss.str();
}

std::string HighResTimer::reportMilliseconds() const
{
  std::ostringstream oss; oss << description_ << ": " << getMilliseconds() << " milliseconds.";
  return oss.str();
}

std::string HighResTimer::reportSeconds() const
{
  std::ostringstream oss; oss << description_ << ": " << getSeconds() << " seconds.";
  return oss.str();
}

std::string HighResTimer::reportMinutes() const
{
  std::ostringstream oss; oss << description_ << ": " << getMinutes() << " minutes.";
  return oss.str();
}

std::string HighResTimer::reportHours() const
{
  std::ostringstream oss; oss << description_ << ": " << getHours() << " hours.";
  return oss.str();
}

std::string HighResTimer::report() const
{
  double val = getMicroseconds();
  if(val <= 1000.0)
    return reportMicroseconds();

  val /= 1000.0;
  if(val <= 1000.0 && val >= 1.0)
    return reportMilliseconds();

  val /= 1000.0;
  if(val <= 60.0 && val >= 1.0)
    return reportSeconds();
  
  val /= 60.0;
  if(val <= 60.0 && val >= 1.0)
    return reportMinutes();
  
  val /= 60.0;
  return reportHours();
}

ScopedTimer::ScopedTimer(const std::string& description) :
  hrt_(description)
{
  hrt_.start();
}

ScopedTimer::~ScopedTimer()
{
  hrt_.stop();
  std::cout << hrt_.report() << std::endl;
}

} // namespace precision_tracking
