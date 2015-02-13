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

	TH1F *h1 = new TH1F("h1","",50,0,209);
	TH1F *h2 = new TH1F("h2","",50,0,10000000000000);
	TH1F *h3 = new TH1F("h3","",100,0,0.063);
	TH1F *h4 = new TH1F("h4","",50,0,10000000000000);
	TH1F *h5 = new TH1F("h5","",100,0,0.063);
	TH1F *h6 = new TH1F("h6","",3,0.5,3.5);

	h1->GetXaxis()->SetTitle("Number of Accesses");
	h1->GetYaxis()->SetTitle("Frequency");
	h1->SetStats(0);
	tree->Draw("nused>>h1");
	gPad->SetLogx();
	gPad->SetLogy();
	c1->SaveAs("Popularity.png");
	
	h2->GetXaxis()->SetTitle("Size of Dataset [GB]");
	h2->GetYaxis()->SetTitle("Frequency");
	h2->SetStats(0);
	tree->Draw("size>>h2");
	c1->SaveAs("Size.png");

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
	c1->SaveAs("Occupancy.png");

	h4->GetXaxis()->SetTitle("Size of Datasets in Cache [GB]");
	h4->GetYaxis()->SetTitle("Frequency");
	h4->SetStats(0);
	for (Long64_t i=0;i<nentries;i++) {
		tree->GetEntry(i);
		if(incache==1)
			h4->Fill(size);
	}
	h4->Draw();
	c1->SaveAs("inCacheSize.png");

	h5->GetXaxis()->SetTitle("Occupancy per Dataset in Cache [Percentage]");
  h5->GetYaxis()->SetTitle("Frequency");
  h5->SetStats(0);
  float inCacheSum = 0;
  for (Long64_t i=0;i<nentries;i++) {
	  tree->GetEntry(i);
	  if(incache==1)
		  inCacheSum += size;
		  TString inCacheOccupancy = Form("size/%f>>h5",inCacheSum);
		  tree->Draw(inCacheOccupancy);
	}
	c1->SaveAs("inCacheOccupancy.png");

  h6->GetXaxis()->SetTitle("Number of Downloads");
	h6->GetYaxis()->SetTitle("Frequency");
	h6->SetStats(0);
	tree->Draw("ndownloads>>h6");
	gPad->SetLogx(0);
	gPad->SetLogy(0);
	TPie *pie = new TPie(h6);
	pie->SetRadius(.3);
	pie->SetEntryFillColor(0,4);
	pie->SetEntryFillColor(1,3);
	pie->SetEntryFillColor(2,2);
	pie->SetEntryLabel(0,"1 Download");
	pie->SetEntryLabel(1,"2 Downloads");
	pie->SetEntryLabel(2,"3 Downloads");
	pie->SetLabelFormat("%perc");
	pie->Draw("nol");
	TLegend *leg = pie->MakeLegend();
 	leg->SetY1(.77); leg->SetY2(.95);
 	leg->SetHeader("Number of Downloads");
	c1->SaveAs("nDownloads.png");

}
