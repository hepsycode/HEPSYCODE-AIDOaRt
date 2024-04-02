#!/bin/bash
hepsycode=$(dirname $BASH_SOURCE)/..
hepsycode=$(cd $hepsycode && pwd)

# export SYSTEMCPATHLIB=/usr/local/systemc-2.3.0a/lib-linux64
# export SYSTEMCPATHINCLUDE=/usr/local/systemc-2.3.0a/include

export SYSTEMCPATHLIB=/usr/local/systemc-2.3.3/lib-linux64
export LD_LIBRARY_PATH=/usr/local/systemc-2.3.3/lib-linux64:$LD_LIBRARY_PATH
export SYSTEMCPATHINCLUDE=/usr/local/systemc-2.3.3/include

