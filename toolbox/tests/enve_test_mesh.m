% % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % %
%                                                                     %
% This file is part of the ENVE project.                              %
%                                                                     %
% Copyright (c) 2020, Davide Stocco, Matteo Larcher and Enrico        %
% Bertolazzi.                                                         %
%                                                                     %
% The ENVE project and its components are supplied under the terms of %
% the open source BSD 3-Clause License. The contents of the ENVE      %
% project and its components may not be copied or disclosed except in %
% accordance with the terms of the BSD 3-Clause License.              %
%                                                                     %
%    Davide Stocco                                                    %
%    Department of Industrial Engineering                             %
%    University of Trento                                             %
%    e-mail: davide.stocco@unitn.it                                   %
%                                                                     %
%    Enrico Bertolazzi                                                %
%    Department of Industrial Engineering                             %
%    University of Trento                                             %
%    e-mail: enrico.bertolazzi@unitn.it                               %
%                                                                     %
% % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % %

% Clear workspace
clc;
clear all;
%close all;

pose = [ ...
  1, 0, 0, 0; ...  
  0, 1, 0, 0; ...  
  0, 0, 1, 0; ...  
  0, 0, 0, 1; ...  
];

% Create mesh from *.rdf
m1 = enve_mesh('../../files_rdf/sample.rdf');
m1.getTriangleground(1);

% Plot output
out1 = figure; hold on;
xlabel('x'); ylabel('y'); zlabel('z');
m1.plot(out1, [0.863 0.863 0.863])

% Create mesh from *.obj
m2 = enve_mesh('../../files_obj/cobblestone.obj', 1.0, pose);
m2.getTriangleground(1);

% Plot output
out2 = figure; hold on;
xlabel('x'); ylabel('y'); zlabel('z');
m2.plot(out2, [0.863 0.863 0.863])
