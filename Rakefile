require_relative "./cmake_utils/Rakefile_common.rb"

CLEAN.include   ["./**/*.o", "./**/*.obj", "./bin", "./build"]
CLEAN.clear_exclude.exclude { |fn| fn.pathmap("%f").downcase == "core" }
CLOBBER.include []

#desc "default task --> build"
task :default => :build

#desc "compile for Visual Studio"
task :build_win do
  # check architecture
  case `where cl.exe`.chop
  when /x64\\cl\.exe/
    VS_ARCH = 'x64'
  when /amd64\\cl\.exe/
    VS_ARCH = 'x64'
  when /bin\\cl\.exe/
    VS_ARCH = 'x86'
  else
    raise RuntimeError, "Cannot determine architecture for Visual Studio".red
  end

  FileUtils.rm_rf   "build"
  FileUtils.mkdir_p "build"
  FileUtils.cd      "build"

  puts "run CMAKE for ENVE".yellow
  sh "cmake -G Ninja -DBITS:VAR=#{VS_ARCH} " + cmd_cmake_build() + ' ..'

  puts "compile with CMAKE for ENVE".yellow
  if COMPILE_DEBUG then
    sh 'cmake --build . --config Debug --target install '+PARALLEL
  else
    sh 'cmake --build . --config Release --target install '+PARALLEL
  end

  FileUtils.cd '..'
end

#desc "compile for OSX/LINUX/MINGW"
task :build_osx_linux_mingw do

  dir = "build"

  FileUtils.rm_rf   dir
  FileUtils.mkdir_p dir
  FileUtils.cd      dir

  puts "run CMAKE for ENVE".yellow
  sh "cmake -G Ninja " + cmd_cmake_build + ' ..'

  puts "compile with CMAKE for ENVE".yellow
  if COMPILE_DEBUG then
    sh 'cmake --build . --config Debug --target install '+PARALLEL
  else
    sh 'cmake --build . --config Release --target install '+PARALLEL
  end

  FileUtils.cd '..'
end

task :clean_osx_linux_mingw do
  FileUtils.rm_rf 'build'
  FileUtils.rm_rf 'lib'
  FileUtils.rm_rf 'lib3rd'
end

task :build_osx   => :build_osx_linux_mingw do end
task :build_linux => :build_osx_linux_mingw do end
task :build_mingw => :build_osx_linux_mingw do end

desc "Build submodules for library compilation OSX/LINUX/MINGW"
task :build_submodules do
  FileUtils.cd 'submodules/acme'
  case OS
  when :mac
    sh 'rake build_osx'
  when :linux
    sh 'rake build_linux'
  when :mingw
    sh 'rake build_mingw'
  when :win
    sh 'rake build_win'
  end
  FileUtils.cd '..'
end

task :clean_osx   => :clean_osx_linux_mingw do end
task :clean_linux => :clean_osx_linux_mingw do end
task :clean_mingw => :clean_osx_linux_mingw do end
task :clean_win   => :clean_osx_linux_mingw do end

desc 'pack for OSX/LINUX/MINGW/WINDOWS'
task :cpack do
  FileUtils.cd "build"
  puts "run CPACK for ENVE".yellow
  sh 'cpack -C CPackConfig.cmake'
  sh 'cpack -C CPackSourceConfig.cmake'
  FileUtils.cd ".."
end
