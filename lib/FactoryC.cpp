// Copyright (c) 2014-2014 Josh Blum
// SPDX-License-Identifier: BSL-1.0

#include <SoapySDR/Device.h>
#include <SoapySDR/Device.hpp>
#include <stdlib.h>
#include <string.h>

SoapySDR::Kwargs toKwargs(const SoapySDRKwargs *args);
SoapySDRKwargs tokwargs(const SoapySDR::Kwargs &args);

extern "C" {

SoapySDRKwargs *SoapySDRDevice_enumerate(const SoapySDRKwargs *args, size_t *length)
{
    const std::vector<SoapySDR::Kwargs> results = SoapySDR::Device::enumerate(toKwargs(args));

    //convert results to out args list
    SoapySDRKwargs *outArgs = (SoapySDRKwargs *)calloc(results.size(), sizeof(SoapySDRKwargs));
    for (size_t i = 0; i < results.size(); i++) outArgs[i] = tokwargs(results[i]);
    *length = results.size();
    return outArgs;
}

SoapySDRDevice *SoapySDRDevice_make(const SoapySDRKwargs *args)
{
    return (SoapySDRDevice *)SoapySDR::Device::make(toKwargs(args));
}

void SoapySDRDevice_unmake(SoapySDRDevice *device)
{
    SoapySDR::Device::unmake((SoapySDR::Device *)device);
}

}