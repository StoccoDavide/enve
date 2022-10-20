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

% Clear workspace
clc;
clear all;
close all;

% Create mesh from *.rdf
m1 = enve_mesh('../../files_rdf/LakeTown.rdf');
m1.getTriangleground(1);

% Plot output
out1 = figure;
m1.plot(out1, [0.863 0.863 0.863])

% Create mesh from *.obj
m2 = enve_mesh('../../files_obj/sample.obj', 1.0);
m2.getTriangleground(1);

% Plot output
out2 = figure;
m2.plot(out2, [0.863 0.863 0.863])
