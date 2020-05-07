#!/bin/bash

# select platform
if [ "$1" == "xenial" ]; then
  plat="Ubuntu 16.04"
  cots_name="maja-cots-ubuntu"
elif [ "$1" == "centos6" ]; then
  plat="CentOS 6"
  cots_name="maja-cots-centos6"
elif [ "$1" == "centos7" ]; then
  plat="CentOS 7"
  cots_name="maja-cots-centos7"
else
  echo Usage: $0  xenial|centos6|centos7
  exit 1
fi

dr_proxy="-e http_proxy -e https_proxy -e ftp_proxy -e no_proxy"
dr_opts="-v ${WORKSPACE}:/opt/src ${dr_proxy}"
majaRegistry="registry.gitlab.cnes.fr/maja/maja"
COTS_SHA1="$(git log -1 --pretty=format:%H -- SuperBuild)"

echo "COTS sha1: ${COTS_SHA1}"

cots_image="${majaRegistry}/${cots_name}:${COTS_SHA1}"

mkdir -p ${WORKSPACE}/out/$1/pkg
chmod 777 ${WORKSPACE}/out/$1/pkg

echo "Building Maja ..."
docker run --name c_maja ${dr_opts} ${cots_image} "-c" "ctest -VV -S /opt/src/CI/maja_build.cmake > /opt/logs/build.log 2>&1 && ctest -VV -S /opt/src/CI/maja_pkg.cmake >> /opt/logs/build.log 2>&1 && rm -rf /opt/build /opt/data"
RET_MAJA=$?

docker cp c_maja:/opt/pkg ${WORKSPACE}/out/$1
docker cp c_maja:/opt/logs/build.log ${WORKSPACE}/out/$1/logs
docker container rm c_maja

exit $RET_MAJA
