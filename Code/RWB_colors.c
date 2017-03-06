      const Int_t NRGBs = 3;//This gives the size of the arrays below.
                            //It's the number of colors between which the gradient shifts.
      const Int_t NCont = 200;
      Double_t stops[NRGBs] = { 0.00, 0.50, 1.00 };//Locations of colors in % of gradient

      Double_t red[NRGBs]   = { 0.00, 1.00, 1.00 };//Treat this like a matrix with each 
      Double_t green[NRGBs] = { 0.00, 1.00, 0.00 };//column as the RGB of the color 
      Double_t blue[NRGBs]  = { 1.00, 1.00, 0.00 };//at each stop.

      TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
      gStyle->SetNumberContours(NCont); 
