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

# Check for a conf file on a upper directory
if File.exists?(File.expand_path('../Rakefile_conf.rb', File.dirname(__FILE__))) then
  require_relative '../Rakefile_conf.rb'
else
  COMPILE_DEBUG      = false
  COMPILE_DYNAMIC    = false
  COMPILE_EXECUTABLE = false
  USE_NMAKE          = true

  case RUBY_PLATFORM
  when /mingw|mswin/
    PARALLEL = ''
    QUIET    = ''
  else
    require 'etc'
    cmakeversion = %x( cmake --version ).scan(/\d+\.\d+\.\d+/).last
    mm = cmakeversion.split('.');
    if mm[0].to_i > 3 || (mm[0].to_i == 3 && mm[1].to_i >= 12) then
      PARALLEL = "--parallel #{Etc.nprocessors} "
      QUIET    = '-- --quiet '
    else
      PARALLEL = ''
      QUIET    = ''
    end
  end
end
