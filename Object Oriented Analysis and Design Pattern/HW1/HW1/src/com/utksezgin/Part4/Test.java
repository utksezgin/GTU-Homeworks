package com.utksezgin.Part4;

public class Test {
    public static void main(String[] args){
        Factory tpxPlaneFactory = new TPXx00PlaneFactory();

        PassengerPlane tpx100Plane = tpxPlaneFactory.createPlane(planeModel.TPX100);
        System.out.println();
        PassengerPlane tpx200Plane = tpxPlaneFactory.createPlane(planeModel.TPX200);
        System.out.println();
        PassengerPlane tpx300Plane = tpxPlaneFactory.createPlane(planeModel.TPX300);
        System.out.println();

        System.out.println(tpx100Plane.getPlaneInfo());
        System.out.println(tpx200Plane.getPlaneInfo());
        System.out.println(tpx300Plane.getPlaneInfo());
    }
}
