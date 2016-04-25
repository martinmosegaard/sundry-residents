#!/bin/bash

## Environment variables for running govc against VMware vSphere

# Set this to avoid a certificate error
export GOVC_INSECURE=1

# Set this to connect to older API versions
export GOVC_MIN_API_VERSION=5.1

export GOVC_URL=changeme
export GOVC_USERNAME=changeme
export GOVC_PASSWORD=changeme

