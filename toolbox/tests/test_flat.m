clc;
clear all;
close all;

% Create flat

f1 = enve_flat([1 2 3]', [1 1 1]', 1.0);

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

p1 = acme_plane([0 0 0]', [0 0 1]');
f1.setPlane(p1)
f1


