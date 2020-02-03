package com.utksezgin.Part4;

/**
 * Factory for creating planes.
 *
 * @author Azmi Utku Sezgin
 */
public abstract class Factory {
    protected String purpose = "";
    protected String skeleton = "";
    protected String engine = "";
    protected int seat = 0;
    protected planeModel model;

    /**
     * Creates a plane from given model
     * @param model plane model to create.
     * @return returns a new plane of given model.
     */
    public abstract PassengerPlane createPlane(planeModel model);

    /**
     * Constructs a skeleton of the model model.
     */
    protected void constructSkeleton() {

        switch(model){
            case TPX100:
                skeleton = "Aluminum alloy";
                break;
            case TPX200:
                skeleton = "Nikel alloy";
                break;
            case TPX300:
                skeleton = "Titanium alloy";
                break;
        }

        System.out.println(skeleton + " skeleton has been constructed.");

    }

    /**
     * Places engines of the given model.
     */
    protected void placeEngines() {

        switch(model){
            case TPX100:
                engine = "Single jet engine";
                break;
            case TPX200:
                engine = "Twin jet engines";
                break;
            case TPX300:
                engine = "Quadro jet engines";
                break;
        }

        System.out.println(engine + " has been placed.");

    }

    /**
     * Places number of seats of the given model.
     */
    protected void placeSeats() {

        switch(model){
            case TPX100:
                seat = 50;
                break;
            case TPX200:
                seat = 100;
                break;
            case TPX300:
                seat = 250;
                break;
        }

        System.out.println(seat + " seats have been placed.");
    }
}

/**
 * Concrete Plane Factory that creates TPX100, TPX200, TPX300 model planes.
 */
class TPXx00PlaneFactory extends Factory{

    @Override
    public PassengerPlane createPlane(planeModel model){
        this.model = model;
        constructSkeleton();
        placeEngines();
        placeSeats();
        if(model == planeModel.TPX100)
            return new TPX100Plane(skeleton, engine, seat, model);
        else if(model == planeModel.TPX200)
            return new TPX200Plane(skeleton, engine, seat, model);
        else
            return new TPX300Plane(skeleton, engine, seat, model);
    }
}