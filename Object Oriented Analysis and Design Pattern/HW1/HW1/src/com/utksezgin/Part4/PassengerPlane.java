package com.utksezgin.Part4;

/**
 * Plane models.
 */
enum planeModel{ TPX100, TPX200, TPX300};

/**
 * Passanger planes
 */
public abstract class PassengerPlane {
    String purpose = "";
    String skeleton = "";
    String engine = "";
    int seat = 0;
    planeModel model;
    int seating = 0;

    /**
     * @return Information of the plane.
     */
    public String getPlaneInfo(){
        return model + " " + purpose + " " + skeleton + " " + engine;
    }
}

/**
 * TPX100 Model plane
 */
class TPX100Plane extends PassengerPlane{
    TPX100Plane(String skeleton, String engine, int seat, planeModel model){
        this.purpose = "Domestic flights";
        this.skeleton = skeleton;
        this.engine = engine;
        this.seat = seat;
        this.model = model;
    }
}

/**
 * TPX200 Model plane
 */
class TPX200Plane extends PassengerPlane{
    TPX200Plane(String skeleton, String engine, int seat, planeModel model){
        this.purpose = "Domestic and short international flights";
        this.skeleton = skeleton;
        this.engine = engine;
        this.seat = seat;
        this.model = model;
    }
}

/**
 * TPX300 Mode plane
 */
class TPX300Plane extends PassengerPlane{
    TPX300Plane(String skeleton, String engine, int seat, planeModel model){
        this.purpose = "Transatlantic flights";
        this.skeleton = skeleton;
        this.engine = engine;
        this.seat = seat;
        this.model = model;
    }
}

