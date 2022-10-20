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

% Clean workspace
clc;
clear all;
close all;

% Create points
p1 = acme_point([0 0 3]')
p2 = acme_point([3 0 0]')
p3 = acme_point([0 3 0]')
p4 = acme_point([1 2  1]')
p5 = acme_point([1 2 -1]')

% Create triangleroad
t1 = enve_triangleground(0, 1.0, p1.get(), p2.get(), p3.get())

% Plot output
out = figure;
t1.plot(out, [0.863 0.863 0.863])
