# Task 6 — Vehicle rental fleet design challenge

## Entities and requirements
Every vehicle has registration, daily rate and rental state. Motor vehicles also have fuel/charge level and service due date. Cars have seating capacity. Electric vehicles include battery capacity and a per-kWh charge component. Fleet operations list, rent and return vehicles; late return incurs a fee. New vehicle types must be addable without changing existing fleet logic.

## Hierarchy
Vehicle (abstract: type(), rentalCharge())
- Bicycle
- MotorVehicle (shared fuel level and service date)
  - TwoWheeler
  - Car (seating capacity)
- ElectricCar (battery kWh and unit rate)
- ElectricBus (extension example)

Fleet owns polymorphic Vehicle pointers in vector<unique_ptr<Vehicle>>. The abstract base has a virtual destructor and pure virtual operations. Rental/return state is common; concrete classes calculate charges.

## Pseudocode
PROCEDURE Rent(vehicle)
  IF vehicle is already rented THEN report error
  ELSE mark vehicle rented
END PROCEDURE

PROCEDURE Return(vehicle, lateDays)
  IF vehicle is not rented OR lateDays < 0 THEN report error
  ELSE calculate fee = lateDays * late-fee rate; mark available; return fee
END PROCEDURE

## Extension
The program creates a bicycle, two-wheeler, car, electric car and ElectricBus. ElectricBus is a new derived type; Fleet and the existing classes are unchanged.

## Alternative: one Vehicle with a type switch
Both switch dispatch and virtual dispatch are O(1) per charge call. A single class stores fields unused by many vehicle types and every new type changes the switch and likely validation logic. A polymorphic object commonly carries a vptr but stores only fields relevant to its concrete type.