#ifndef __TGEMSBSGEMCHAMBER_H
#define __TGEMSBSGEMCHAMBER_H

#include "THaDetector.h"
#include "TGEMSBSBox.h"

class THaEvData;
class TGEMSBSGEMPlane;

// In the SBS geometry, a chamber is a box (as defined it TGEMSBSBox class). 
// Refer to the comment in the header of TGEMSBSBox class for more info.

// It uses many of the methods from this class (namely the transformations methods),
// which it completes by offering the options to use these methods
// with a TVector3 object as an input instead of 3 doubles.

// TGEMSBSGEMChamber also inherits form THaDetector, which grants it all the functions from its class
// (see http://hallaweb.jlab.org/podd/doc/html_v16/ClassIndex.html for more info).

class TGEMSBSGEMChamber : public THaDetector {
 public:
  //Constructors and destructor
  TGEMSBSGEMChamber(const char *name, const char *desc);//It is recommended to use this constructor
  TGEMSBSGEMChamber() : fPlanes(0), fNPlanes(0), fBox(0) {} // for ROOT RTTI

  virtual ~TGEMSBSGEMChamber();
  
  //Read the geometry for the TGEMSBSBox in the data base
  Int_t ReadDatabase (const TDatime& date);
  Int_t ReadGeometry (FILE* file, const TDatime& date, Bool_t required);
  const char* GetDBFileName() const;

  Int_t Decode( const THaEvData & );

  // Return positions of chamber edges, in its own reference frame, in meters
  Double_t GetLowerEdgeX() const {return -(GetSize())[0]/2;}
  Double_t GetLowerEdgeY() const {return -(GetSize())[1]/2;}
  Double_t GetUpperEdgeX() const {return +(GetSize())[0]/2;}
  Double_t GetUpperEdgeY() const {return +(GetSize())[1]/2;}

  TGEMSBSBox& GetBox() const {return *fBox;};
  
  // Frame conversions
  void HallCenterToPlane (Double_t& x, Double_t& y, Double_t& z) const {
    fBox->HallCenterToBox (x, y, z);
  };  // input and output in mm
  void HallCenterToSpec (Double_t& x, Double_t& y, Double_t& z) const {
    fBox->HallCenterToSpec (x, y, z);
  };  // input and output in mm
  void LabToPlane (Double_t& x, Double_t& y, Double_t& z) const {
    fBox->LabToBox (x, y, z);
  };  // input and output in mm
  void HallCenterToLab (Double_t& x, Double_t& y, Double_t& z) const {
    fBox->HallCenterToLab (x, y, z);
  };  // input and output in mm
  void LabToSpec (Double_t& x, Double_t& y, Double_t& z) const {
    fBox->LabToSpec (x, y, z);
  };  // input and output in mm
  void SpecToPlane (Double_t& x, Double_t& y, Double_t& z) const {
    z = z-fBox->GetD0()*1.0e3;
    fBox->SpecToBox (x, y);
  };  // input and output in mm
  void PlaneToSpec (Double_t& x, Double_t& y, Double_t& z) const {
    z = z+fBox->GetD0()*1.0e3;
    fBox->BoxToSpec (x, y);
  };  // input and output in mm
  void SpecToLab (Double_t& x, Double_t& y, Double_t& z) const {
    fBox->SpecToLab (x, y, z);
  };  // input and output in mm
  void LabToHallCenter (Double_t& x, Double_t& y, Double_t& z) const {
    fBox->LabToHallCenter (x, y, z);
  };  // input and output in mm
  void PlaneToLab (Double_t& x, Double_t& y, Double_t& z) const {
    fBox->BoxToLab (x, y, z);
  };  // input and output in mm
  void SpecToHallCenter (Double_t& x, Double_t& y, Double_t& z) const {
    fBox->SpecToHallCenter (x, y, z);
  };  // input and output in mm
  void PlaneToHallCenter (Double_t& x, Double_t& y, Double_t& z) const {
    fBox->BoxToHallCenter (x, y, z);
  };  // input and output in mm

  
  //Frame conversions with TVector3 objects as inputs
  void HallCenterToPlane (TVector3& X_) const;  // input and output in mm
  void HallCenterToSpec (TVector3& X_) const;  // input and output in mm
  void LabToPlane (TVector3& X_) const;
  void HallCenterToLab (TVector3& X_) const;  // input and output in mm
  void LabToSpec (TVector3& X_) const;
  void SpecToPlane (TVector3& X_) const;
  void PlaneToSpec (TVector3& X_) const;
  void SpecToLab (TVector3& X_) const;
  void LabToHallCenter (TVector3& X_) const;  // input and output in mm
  void PlaneToLab (TVector3& X_) const;
  void SpecToHallCenter (TVector3& X_) const;  // input and output in mm
  void PlaneToHallCenter (TVector3& X_) const;  // input and output in mm
  
  // Access to the info of TGEMSBSGEMPlane which is regarded as a subdetector of TGEMSBSGEMChamber.
  // (see comments in the code of class TGEMSBSGEMPlane)
   UInt_t GetNPlanes() const {return fNPlanes;};
    
  TGEMSBSGEMPlane& GetPlane (UInt_t i) const {return *(fPlanes[i]);};
  Int_t InitPlane (const UInt_t i, const char* name, const char* desc);
  virtual void Print ( Option_t* opt="P" ) const;

 private:
  TGEMSBSGEMPlane** fPlanes; // List of planes
  UInt_t fNPlanes;
  TGEMSBSBox* fBox;  // Box geometry

  ClassDef(TGEMSBSGEMChamber,0)

};

#endif//__TGEMSBSGEMCHAMBER_H
