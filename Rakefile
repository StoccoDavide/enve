# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#                                                                     #
# The ENVE project                                                    #
#                                                                     #
# Copyright (c) 2020, Davide Stocco and Enrico Bertolazzi.            #
#                                                                     #
# The ENVE project can not be copied and/or distributed without the   #
# express permission of Davide Stocco and Enrico Bertolazzi.          #
#                                                                     #
#    Davide Stocco                                                    #
#    Department of Industrial Engineering                             #
#    University of Trento                                             #
#    e-mail: davide.stocco@unitn.it                                   #
#                                                                     #
#    Enrico Bertolazzi                                                #
#    Department of Industrial Engineering                             #
#    University of Trento                                             #
#    e-mail: enrico.bertolazzi@unitn.it                               #
#                                                                     #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

%w(colorize rake fileutils).each do |gem|
  begin
    require gem
  rescue LoadError
    warn "Install the #{gem} gem:\n $ (sudo) gem install #{gem}".magenta
    exit 1
  end
end

require_relative "./Rakefile_common.rb"

file_base = File.expand_path(File.dirname(__FILE__)).to_s

cmd_cmake_build = ""
if COMPILE_EXECUTABLE then
  cmd_cmake_build += ' -DBUILD_EXECUTABLE:VAR=true '
else
  cmd_cmake_build += ' -DBUILD_EXECUTABLE:VAR=false '
end
if COMPILE_DYNAMIC then
  cmd_cmake_build += ' -DBUILD_SHARED:VAR=true '
else
  cmd_cmake_build += ' -DBUILD_SHARED:VAR=false '
end
if COMPILE_DEBUG then
  cmd_cmake_build += ' -DCMAKE_BUILD_TYPE:VAR=Debug --loglevel=STATUS '
else
  cmd_cmake_build += ' -DCMAKE_BUILD_TYPE:VAR=Release --loglevel=STATUS '
end
cmd_cmake_build += " -DINSTALL_HERE:VAR=true "

task :default => [:build]

TESTS = [
]

desc "run tests"
task :run do
  puts "Run test".yellow
  Dir.glob('bin/*') do |cmd|
    next if cmd =~ /.manifest$|.dSYM$|.txt$/
    puts "execute: #{cmd}".yellow
    sh cmd
  end
end

task :build_gen do

  dir = "build"

  FileUtils.rm_rf   dir
  FileUtils.mkdir_p dir
  FileUtils.cd      dir

  cmd_cmake = "cmake " + cmd_cmake_build

  puts "run CMAKE for ENVE".yellow
  sh cmd_cmake + ' ..'
  puts "compile with CMAKE for ENVE".yellow
  if COMPILE_DEBUG then
    sh 'cmake --build . --config Debug --target install '+PARALLEL+QUIET
  else
    sh 'cmake --build . --config Release --target install '+PARALLEL+QUIET
  end
  FileUtils.cd '..'
end

desc 'compile for OSX'
task :build_osx => :build_gen do |t, args|
end

desc 'compile for LINUX'
task :build_linux => :build_gen do |t, args|
end

desc "compile for Visual Studio [default year=2017, bits=x64]"
task :build_win, [:year, :bits] do |t, args|

  args.with_defaults( :year => "2017", :bits => "x64" )

  dir = "vs_#{args.year}_#{args.bits}"

  FileUtils.rm_rf   dir
  FileUtils.mkdir_p dir
  FileUtils.cd      dir

  cmd_cmake = win_vs(args.bits,args.year) + cmd_cmake_build

  puts "run CMAKE for ENVE".yellow
  sh cmd_cmake + ' ..'
  puts "compile with CMAKE for ENVE".yellow
  if COMPILE_DEBUG then
    sh 'cmake --build . --config Debug --target install '+PARALLEL+QUIET
  else
    sh 'cmake  --build . --config Release  --target install '+PARALLEL+QUIET
  end

  FileUtils.cd '..'
end

desc "build for OSX/LINUX/WINDOWS"
task :build do
  if (/cygwin|mswin|mingw|bccwin|wince|emx/ =~ RUBY_PLATFORM) != nil then
    # LINUX
    Rake::Task["build_linux"].invoke
  elsif (/darwin/ =~ RUBY_PLATFORM) != nil then
    # OSX
    Rake::Task["build_osx"].invoke
  else
    # WINDOWS
    Rake::Task["build_windows"].invoke
  end
end

task :clean_gen do
  FileUtils.rm_rf 'lib'
  FileUtils.rm_rf 'lib3rd'
end

desc "clean for OSX"
task :clean_osx => :clean_gen do
end

desc "clean for LINUX"
task :clean_linux => :clean_gen do
end

desc "clean for WINDOWS"
task :clean_win do
  FileUtils.rm_rf 'lib'
  FileUtils.rm_rf 'lib3rd'
  FileUtils.rm_rf 'vs_*'
end

desc "clean for OSX/LINUX/WINDOWS"
task :clean do
  if (/cygwin|mswin|mingw|bccwin|wince|emx/ =~ RUBY_PLATFORM) != nil then
    # LINUX
    Rake::Task["clean_linux"].invoke
  elsif (/darwin/ =~ RUBY_PLATFORM) != nil then
    # OSX
    Rake::Task["clean_linux"].invoke
  else
    # WINDOWS
    Rake::Task["clean_linux"].invoke
  end
end
