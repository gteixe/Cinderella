{
	TTree *tree = new TTree("tree", "tree");
	tree->ReadFile("snapshotCinderellaDb.txt", "name/C:nused/I:ndownloads:incache:entrydate:size/F");
	Char_t name;
	Int_t nused, ndownloads, incache, entrydate;
	Float_t size;
	tree->SetBranchAddress("name",&name);
	tree->SetBranchAddress("nused",&nused);
	tree->SetBranchAddress("ndownloads",&ndownloads);
	tree->SetBranchAddress("incache",&incache);
	tree->SetBranchAddress("entrydate",&entrydate);
	tree->SetBranchAddress("size",&size);

	Long64_t nentries = tree->GetEntries();

	TDatime date;
	TString dateTime = date.AsSQLString();
	TString text;
	text = TString("Last Update: ") + dateTime;
	TText *update = new TText(0.025,0.025,text.Data());
	update->SetTextSize(0.04);
	update->SetTextColor(kBlue);

	TH1F *h1 = new TH1F("h1","",50,0,209);
	TH1F *h2 = new TH1F("h2","",50,0,10000);
	TH1F *h3 = new TH1F("h3","",100,0,0.063);
	TH1F *h4 = new TH1F("h4","",50,0,10000);
	TH1F *h5 = new TH1F("h5","",100,0,0.063);
	TH1F *h6 = new TH1F("h6","",3,0.5,3.5);

	TPie *pie1 = new TPie("","",3);
	pie1->SetRadius(0.3);
	float slice0 = 0;
	float slice1 = 0;
	float slice2 = 0;
	for (Long64_t i=0;i<nentries;i++) {
     	  tree->GetEntry(i);
     	  if(nused<10){
     	    slice0 += 1;
     	  }
     	  if(nused>=10,nused<100){
     	    slice1 += 1;
     	  }
     	  if(nused>=100){
     	    slice2 += 1;
     	  }
        }
        pie1->GetSlice(0)->SetValue(slice0);
    	pie1->GetSlice(1)->SetValue(slice1);
    	pie1->GetSlice(2)->SetValue(slice2);
	pie1->SetEntryFillColor(0,4);
	pie1->SetEntryFillColor(1,3);
	pie1->SetEntryFillColor(2,2);
	pie1->SetEntryLabel(0,"Less than 10 accesses");
	pie1->SetEntryLabel(1,"10-100 accesses");
	pie1->SetEntryLabel(2,"100+ accesses");
	pie1->SetLabelFormat("%perc");
	pie1->Draw("nol");
	TLegend *leg1 = pie1->MakeLegend();
 	leg1->SetY1(.77); leg1->SetY2(.95);
 	leg1->SetHeader("Popularity");
	update->DrawTextNDC(0.025,0.025,text.Data());
	c1->SaveAs("Popularity.png");
	c1->Clear();
	
	h2->GetXaxis()->SetTitle("Size of Dataset [GB]");
	h2->GetYaxis()->SetTitle("Frequency");
	h2->SetStats(0);
	float gigabyteScaling = 1000000000;
	TString sizeOfDatasets = Form("size/%f>>h2",gigabyteScaling);
	tree->Draw(sizeOfDatasets);
	gPad->SetLogx();
	gPad->SetLogy();
	update->DrawTextNDC(0.025,0.025,text.Data());
	c1->SaveAs("Size.png");
	c1->Clear();

	h3->GetXaxis()->SetTitle("Ocuppancy per Dataset [Percentage]");
	h3->GetYaxis()->SetTitle("Frequency");
	h3->SetStats(0);
	float sizeSum = 0;
   	for (Long64_t i=0;i<nentries;i++) {
     	  tree->GetEntry(i);
     	  sizeSum += size;
        }
        TString occupancy = Form("size/%f>>h3",sizeSum);
	tree->Draw(occupancy);
	update->DrawTextNDC(0.025,0.025,text.Data());
	c1->SaveAs("Occupancy.png");
	c1->Clear();

	h4->GetXaxis()->SetTitle("Size of Datasets in Cache [GB]");
	h4->GetYaxis()->SetTitle("Frequency");
	h4->SetStats(0);
	for (Long64_t i=0;i<nentries;i++) {
	  tree->GetEntry(i);
	  if(incache==1){
	    h4->Fill(.000000001*size);
	  }
	}
	h4->Draw();
	update->DrawTextNDC(0.025,0.025,text.Data());
	c1->SaveAs("inCacheSize.png");
	c1->Clear();

	h5->GetXaxis()->SetTitle("Occupancy per Dataset in Cache [Percentage]");
   	h5->GetYaxis()->SetTitle("Frequency");
   	h5->SetStats(0);
   	float inCacheSum = 0;
   	for (Long64_t i=0;i<nentries;i++) {
	  tree->GetEntry(i);
	  if(incache==1){
	    inCacheSum += size;
	    TString inCacheOccupancy = Form("size/%f>>h5",inCacheSum);
	    tree->Draw(inCacheOccupancy);
	  }
	}
	update->DrawTextNDC(0.025,0.025,text.Data());
	c1->SaveAs("inCacheOccupancy.png");
	c1->Clear();

   	h6->GetXaxis()->SetTitle("Number of Downloads");
	h6->GetYaxis()->SetTitle("Frequency");
	h6->SetStats(0);
	tree->Draw("ndownloads>>h6");
	gPad->SetLogx(0);
	gPad->SetLogy(0);
	TPie *pie2 = new TPie(h6);
	pie2->SetRadius(.3);
	pie2->SetEntryFillColor(0,4);
	pie2->SetEntryFillColor(1,3);
	pie2->SetEntryFillColor(2,2);
	pie2->SetEntryLabel(0,"1 Download");
	pie2->SetEntryLabel(1,"2 Downloads");
	pie2->SetEntryLabel(2,"3 Downloads");
	pie2->SetLabelFormat("%perc");
	pie2->Draw("nol");
	TLegend *leg2 = pie2->MakeLegend();
 	leg2->SetY1(.77); leg2->SetY2(.95);
 	leg2->SetHeader("Number of Downloads");
	update->DrawTextNDC(0.025,0.025,text.Data());
	c1->SaveAs("nDownloads.png");
	c1->Clear();	

}
