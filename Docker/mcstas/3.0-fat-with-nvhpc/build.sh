#!/usr/bin/env bash
containername="mccode/mcstas-3.0:1.3"
docker image build --tag $containername .

echo Build of $containername done.
