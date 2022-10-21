#!/usr/bin/ruby -w

require 'fileutils'

FileUtils.rm_rf "./src/*"

FileUtils.cp_r '../cmake_utils/.', "./cmake_utils";

FileUtils.cp_r '../src/.',                                  "./src";
FileUtils.cp_r '../submodules/acme/src/.',                  "./src";
FileUtils.cp_r '../submodules/acme/submodules/Utils/src/.', "./src";

FileUtils.cp "../LICENSE.txt", "license.txt";
