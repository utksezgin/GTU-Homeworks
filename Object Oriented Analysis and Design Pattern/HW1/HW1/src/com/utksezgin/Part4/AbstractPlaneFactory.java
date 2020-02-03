package com.utksezgin.Part4;

/**
 * Abstract plane factory for creating planes for Domestic, Eurasia, Other markets.
 */
public abstract class AbstractPlaneFactory {

    protected String purpose = "";
    protected String skeleton = "";
    protected String engine = "";
    protected int seat = 0;
    protected planeModel model;

    /**
     * Constructs skeleton of the given model. ALl the skeleton types are same for each market.
     */
    protected void constructSkeleton() {

        switch (model) {
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
     * Places engines from different markets and for different models.
     */
    public abstract void placeEngines();

    /**
     * Places seats from different markets and for different models.
     */
    public abstract void placeSeats();

    public PassengerPlane createPlane(planeModel model) {
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

/**
 * Plane factory for domestic market that can create any model of plane.
 */
class DomesticPlaneFactory extends AbstractPlaneFactory {
    @Override
    public void placeEngines() {
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

        System.out.println("Turbojet type " + engine + " has been placed.");
    }

    @Override
    public void placeSeats() {
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
        System.out.println(seat + " velvet seats have been placed.");
    }
}

/**
 * Plane factory for eurasia market that can create any model of plane.
 */
class EurasiaPlaneFactory extends AbstractPlaneFactory {
    @Override
    public void placeEngines() {
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

        System.out.println("Turbofan type " + engine + " has been placed.");
    }

    @Override
    public void placeSeats() {
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
        System.out.println(seat + " linen seats have been placed.");
    }
}

/**
 * Plane factory for other market that can create any model of plane.
 */
class OtherPlaneFactory extends AbstractPlaneFactory {
    @Override
    public void placeEngines() {
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

        System.out.println("Geared turbofan type " + engine + " has been placed.");
    }

    @Override
    public void placeSeats() {
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
        System.out.println(seat + " leather seats have been placed.");
    }
}