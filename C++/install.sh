#!/bin/sh

## Licensed under the Apache License, Version 2.0 (the "License");
## you may not use this file except in compliance with the License.
## You may obtain a copy of the License at

##     http://www.apache.org/licenses/LICENSE-2.0

## Unless required by applicable law or agreed to in writing, software
## distributed under the License is distributed on an "AS IS" BASIS,
## WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
## See the License for the specific language governing permissions and
## limitations under the License.
###########################################################################
###########################################################################
## Install dependencies

# Exit script if any command fails
set -e

# Print the commands being run (optional for debugging)
set -x

## clone matplotlib-cpp
repository_matplotlib="https://github.com/lava/matplotlib-cpp.git"
localFolder_matplotlib="lib/matplotlib"
git clone "$repository_matplotlib" "$localFolder_matplotlib"

## clone eigne
repository_eigen="https://gitlab.com/libeigen/eigen.git"
localFolder_eigen="lib/Eigen"
git clone "$repository_eigen" "$localFolder_eigen"

## clone json
repository_json="https://github.com/nlohmann/json.git"
localFolder_json="lib/Json"
git clone "$repository_json" "$localFolder_json"
