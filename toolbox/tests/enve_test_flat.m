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
close all;

% Create flat
f1 = enve_flat(1.0, [1 2 3]', [1 1 1]');
f1

% Plot output
out1 = figure;
f1.plot(out1, [0.863 0.863 0.863])

% Test get
f1.getOrigin()
f1.getNormal()
f1.getFriction()
f1.getPlane()

% Test set
f1.setOrigin([1 1 1]')
f1.setNormal([0 0 1]')
f1.setFriction(0.8)
f1

p1 = acme_plane([0 0.5 0]', [0 0 1]');
f1.setPlane(p1)
f1
