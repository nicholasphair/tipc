#!/usr/bin/env bash
declare -r ANTLR_VERSION=4
declare -r JAVA_VERSION=8
declare -r LLVM_MAJOR_VERSION=10
declare -r LLVM_VERSION=${LLVM_MAJOR_VERSION}.0.0
declare -r LLVM_MACOS_BINARY_URL=https://github.com/llvm/llvm-project/releases/download/llvmorg-${LLVM_VERSION}/clang+llvm-${LLVM_VERSION}-x86_64-apple-darwin.tar.xz
declare -r LLVM_MACOS_DIR=${HOME}/llvm

echogreen() {
  local green=$(tput setaf 2)
  local reset=$(tput sgr0)
  echo "${green}${@}${reset}"
}

echoerr() { 
  local red=$(tput setaf 1)
  local reset=$(tput sgr0)
  echo "${red}${@}${reset}" 1>&2; 
}


bootstrap_ubuntu_dependencies() {
  wget -O- https://apt.corretto.aws/corretto.key | sudo apt-key add -
  sudo add-apt-repository 'deb https://apt.corretto.aws stable main'
  sudo apt -y update

  sudo apt -y install \
    java-1.$JAVA_VERSION.0-amazon-corretto-jdk \
    git \
    cmake \
    pkg-config \
    uuid-dev \
    antlr$ANTLR_VERSION \
    zlib1g-dev \
    lcov

  sudo bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)"

  sudo apt -y install \
    libllvm-$LLVM_MAJOR_VERSION-ocaml-dev \
    libllvm$LLVM_MAJOR_VERSION \
    llvm-$LLVM_MAJOR_VERSION \
    llvm-$LLVM_MAJOR_VERSION-dev \
    llvm-$LLVM_MAJOR_VERSION-doc \
    llvm-$LLVM_MAJOR_VERSION-examples \
    llvm-$LLVM_MAJOR_VERSION-runtime

  sudo apt -y install \
    clang-$LLVM_MAJOR_VERSION \
    clang-tools-$LLVM_MAJOR_VERSION \
    clang-$LLVM_MAJOR_VERSION-doc \
    libclang-common-$LLVM_MAJOR_VERSION-dev \
    libclang-$LLVM_MAJOR_VERSION-dev \
    libclang1-$LLVM_MAJOR_VERSION \
    clang-format-$LLVM_MAJOR_VERSION \
    python3-clang-$LLVM_MAJOR_VERSION \
    clangd-$LLVM_MAJOR_VERSION
}


bootstrap_ubuntu_env() {
  echo export TIPCLANG=$(which clang-$LLVM_MAJOR_VERSION) >> ~/.bashrc
}


bootstrap_ubuntu() {
  bootstrap_ubuntu_dependencies
  bootstrap_ubuntu_env
}


bootstrap_linux() {
  . /etc/os-release
  if [ $ID == ubuntu -o $ID == pop ]; then
    bootstrap_ubuntu
  else
    echoerr $ID is not supported.
    exit 1
  fi
}

bootstrap_mac_env() {
  local LLVM_INSTALL_DIR=${LLVM_MACOS_DIR}/$(basename ${LLVM_MACOS_BINARY_URL} .tar.xz)
  echo export CC=${LLVM_INSTALL_DIR}/bin/clang >> ~/.bashrc
  echo export CXX=${LLVM_INSTALL_DIR}/bin/clang++ >> ~/.bashrc
  echo export LLVM_DIR=${LLVM_INSTALL_DIR}/lib/cmake >> ~/.bashrc
  echo export TIPCLANG=${LLVM_INSTALL_DIR}/bin/clang >> ~/.bashrc
}

bootstrap_mac_dependencies() {
  if ! [ -x "$(command -v brew)" ]; then
    echoerr error: Homebrew is not installed.
    exit 1
  fi

  brew install homebrew/cask-versions/corretto$JAVA_VERSION
  brew install \
    git \
    cmake \
    pkg-config \
    antlr@$ANTLR_VERSION \
    lcov

  mkdir -p ${LLVM_MACOS_DIR}
  wget ${LLVM_MACOS_BINARY_URL} --output-document ${LLVM_MACOS_DIR}/$(basename ${LLVM_MACOS_BINARY_URL})
  tar xzf ${LLVM_MACOS_DIR}/$(basename ${LLVM_MACOS_BINARY_URL}) --cd ${LLVM_MACOS_DIR}

}


bootstrap_mac() {
  bootstrap_mac_dependencies
  bootstrap_mac_env
}


bootstrap() {
  local unameOut="$(uname -s)"
  case "${unameOut}" in
    Linux*)
      bootstrap_linux;;
    Darwin*)
      bootstrap_mac;;
    *)
      echoerr error: Script has not been implemented for: ${unameOut}.
      exit 1
      ;;
  esac

  echo 
  echo --------------------------------------------------------------------------------
  echo * bashrc has been updated - be sure to source the file or restart your shell.  *
  echo --------------------------------------------------------------------------------
}

bootstrap

