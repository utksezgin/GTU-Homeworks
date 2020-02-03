package com.utksezgin.Part4;

public class AbstractTest {
    public static void main(String[] args){
        AbstractPlaneFactory domesticPlaneFactory = new DomesticPlaneFactory();
        AbstractPlaneFactory eurisiaPlaneFactory = new EurasiaPlaneFactory();
        AbstractPlaneFactory otherPlaneFactory = new OtherPlaneFactory();

        PassengerPlane tpx100Plane = domesticPlaneFactory.createPlane(planeModel.TPX100);
        System.out.println(tpx100Plane.getPlaneInfo() + "- has been created.");
        System.out.println();
        PassengerPlane tpx200Plane = eurisiaPlaneFactory.createPlane(planeModel.TPX200);
        System.out.println(tpx200Plane.getPlaneInfo() + "- has been created.");
        System.out.println();
        PassengerPlane tpx300Plane = otherPlaneFactory.createPlane(planeModel.TPX300);
        System.out.println(tpx300Plane.getPlaneInfo() + "- has been created.");
        System.out.println();
    }
}
