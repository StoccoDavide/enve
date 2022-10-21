% % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % %
%                                                                     %
% This file is part of the ENVE project.                              %
%                                                                     %
% Copyright (c) 2022, Davide Stocco. All rights reserved.             %
%                                                                     %
% The ENVE project can not be copied and/or distributed without       %
% the express permission of Davide Stocco.                            %
%                                                                     %
%    Davide Stocco                                                    %
%    Department of Industrial Engineering                             %
%    University of Trento                                             %
%    e-mail: davide.stocco@unitn.it                                   %
%                                                                     %
% % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % %

clear all;
clear functions;
clear mex;
clc;

if ismac
  oldPath = getenv('PATH');
  newPath = strcat(oldPath, pathsep, '/usr/local/bin'); % on MAC
  setenv('PATH', newPath);
elseif isunix
elseif ispc
  oldPath = getenv('PATH');
  newPath = strcat(oldPath, pathsep, 'C:\Program Files\CMake\bin'); % on Windows
  setenv('PATH', newPath);
end

old_dir = cd(fileparts(which(mfilename)));
cd('..');
%system('rmdir /S build');
numcores = feature('numcores');

if isfolder('build')
  rmdir('build','s')
end
if false
  CMD1 = 'cmake -G "Ninja" -DCMAKE_BUILD_TYPE:STRING=Debug -Bbuild -S .';
  CMD2 = 'ninja -C build';
else
  CMD1 = 'cmake -G "Ninja" -DCMAKE_BUILD_TYPE:STRING=Release -Bbuild -S .';
  CMD2 = 'ninja -C build';
end

fprintf( '%s\n%s\n', CMD1, CMD2 );

system(CMD1);
system(CMD2);

cd(old_dir);