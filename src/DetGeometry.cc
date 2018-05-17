//Вариант 2
//Реализовать составную геометрию представленную на рисунке
#include <fstream>
#include <G4Sphere.hh>
#include <G4Colour.hh>
#include "DetGeometry.hh"

using namespace std;

DetGeometry::DetGeometry() {
    world_sizeXYZ   = 50 * m;
    nist            = G4NistManager::Instance();
    world_mat       = nist->FindOrBuildMaterial("G4_AIR");
    solidWorld      = new G4Box("solWorld", 0.5*world_sizeXYZ, 0.5*world_sizeXYZ, 0.5*world_sizeXYZ);
    logicWorld      = new G4LogicalVolume(solidWorld, world_mat, "logWorld");
    physWorld       = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "phyWorld", 0, false, 0);
    G4cout<<"Geometry of detector is build successfully\t\t\t\t\t\tOK!!!"<<G4endl;
}

DetGeometry::~DetGeometry() {}

G4VPhysicalVolume* DetGeometry::Construct(){
    G4Material * material       = nist->FindOrBuildMaterial("G4_Fe");

    G4Isotope* La138=new G4Isotope("La138",57,138);
    G4Isotope* La139=new G4Isotope("La139",57,139);
    G4Element* La=new G4Element("Lantan","La",2);
    La->AddIsotope(La138,0.01*perCent);
    La->AddIsotope(La139,99.9*perCent);

     G4Isotope* Br79=new G4Isotope("Br79",35,79);
     G4Isotope* Br81=new G4Isotope("Br81",35,81);
     G4Isotope* Br83=new G4Isotope("Br83",35,83);
     G4Element* Br=new G4Element("Brom","Br",3);
    Br->AddIsotope(Br79,10.3*perCent);
    Br->AddIsotope(Br81,49.7*perCent);
    Br->AddIsotope(Br83,40*perCent);

    G4Isotope* Ce138=new G4Isotope("Ce138",58,138);
    G4Isotope* Ce136=new G4Isotope("La139",58,136);
    G4Element* Ce=new G4Element("Cerium","Ce",2);
    Ce->AddIsotope(Ce138,67.6*perCent);
    Ce->AddIsotope(Ce136,32.4*perCent);

    G4Material* LaBr3_Ce=new G4Material("LaBr3(Ce)",5.29*g/cm3,3,kStateSolid);
    LaBr3_Ce->AddElement(La,2);
    LaBr3_Ce->AddElement(Br,3);
    LaBr3_Ce->AddElement(Ce,2);

    G4Isotope* Al26=new G4Isotope("Al26",13,26);
    G4Isotope* Al27=new G4Isotope("Al27",13,27);
    G4Element* Al=new G4Element("Aluminium","Al",2);
    Al->AddIsotope(Al26,96.4*perCent);
    Al->AddIsotope(Al27,3.6*perCent);

    G4Isotope* Mg24=new G4Isotope("Mg24",12,24);
    G4Isotope* Mg25=new G4Isotope("Mg25",12,25);
    G4Isotope* Mg26=new G4Isotope("Mg26",12,26);
    G4Element* Mg=new G4Element("Magnium","Mg",3);
    Mg->AddIsotope(Mg24,23.99*perCent);
    Mg->AddIsotope(Mg25,24.99*perCent);
    Mg->AddIsotope(Mg26,51.2*perCent);

    G4Isotope* Mn55=new G4Isotope("Mg24",25,55);
    G4Isotope* Mn53=new G4Isotope("Mg25",25,53);
    G4Element* Mn=new G4Element("Manganese","Mn",2);
    Mn->AddIsotope(Mn55,73.5*perCent);
    Mn->AddIsotope(Mn53,26.5*perCent);

    G4Isotope* Si28=new G4Isotope("Si28",14,14);
    G4Isotope* Si29=new G4Isotope("Si29",14,15);
    G4Isotope* Si30=new G4Isotope("Si30",14,16);
    G4Element* Si=new G4Element("Silicon","Si",3);
    Si->AddIsotope(Si28,28.9*perCent);
    Si->AddIsotope(Si29,56.2*perCent);
    Si->AddIsotope(Si30,14.9*perCent);

    G4Isotope* Fe54=new G4Isotope("Si28",26,54);
    G4Isotope* Fe56=new G4Isotope("Si29",26,56);
    G4Isotope* Fe57=new G4Isotope("Si30",26,57);
    G4Isotope* Fe58=new G4Isotope("Si30",26,58);
    G4Element* Fe=new G4Element("Ferium","Fe",4);
    Fe->AddIsotope(Fe54,13.7*perCent);
    Fe->AddIsotope(Fe56,54.1*perCent);
    Fe->AddIsotope(Fe57,20.7*perCent);
    Fe->AddIsotope(Fe58,11.5*perCent);

    G4Isotope* Cu63=new G4Isotope("Cu29",29,54);
    G4Isotope* Cu65=new G4Isotope("Si29",29,56);
    G4Element* Cu=new G4Element("Copper","Cu",2);
    Cu->AddIsotope(Cu63,69.1*perCent);
    Cu->AddIsotope(Cu65,30.9*perCent);

    G4Material* AMr2=new G4Material("AMr2",3.24*g/cm3,6,kStateSolid);
    AMr2->AddElement(Mg,3);
    AMr2->AddElement(Si,3);
    AMr2->AddElement(Fe,4);
    AMr2->AddElement(Cu,2);
    AMr2->AddElement(Al,2);
    AMr2->AddElement(Mn,2);

    auto sphere=new G4Sphere("Sphere",0,10.*cm,0,360.*deg,0*deg,180.*deg);
    auto sphere_log=new G4LogicalVolume(sphere,LaBr3_Ce,"sphere");
    auto sphere_PV=new G4PVPlacement(0,G4ThreeVector(0,0,0),sphere_log,"sphere_PV",logicWorld,false,0);
    sphere_log->SetVisAttributes(G4Colour::Green());

    auto box=new G4Box("Box",10.*cm,10.*cm,10.*cm);
    auto box_log=new G4LogicalVolume(box,AMr2,"sphere");
    auto box_PV=new G4PVPlacement(0,G4ThreeVector(0,0,0),box_log,"box_PV",logicWorld,false,0);
    box_log->SetVisAttributes(G4Colour::Blue());

    ofstream fout("../result.txt");
    fout<<"\n"<<LaBr3_Ce;
    fout<<"\n"<<AMr2;
    fout<<"\n\n\n\n"<<box_log->GetMass(false)/g<<endl;
    fout<<"\n\n\n\n"<<sphere_log->GetMass(false)/g<<endl;
    fout.close();
    //еще и на экран
    cout<<LaBr3_Ce<<endl;
    cout<<box_log->GetMass(false)/g<<endl;
    cout<<AMr2<<endl;
    cout<<sphere_log->GetMass(false)/g<<endl;


    return physWorld;
}


