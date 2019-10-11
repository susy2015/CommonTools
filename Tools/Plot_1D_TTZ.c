#include "CrossSection.C"
#include "Plot_1D_AUX.c"
int Plot_1D_TTZ()
{
	//gROOT->ForceStyle();

	double lumi = 36; //2016
	//lumi = 42; //2017
	//lumi = 137; //2018
	TString year = "_2016";
	bool plot_log = false;
	plot_log = true;
	bool plot_sig_pad = true;
	bool plot_BG = true;
	bool use_low_stat_sig = false;
	//use_low_stat_sig = true;
	bool sig_scale_to_BG = true;
	bool use_original_title = false;

	TString result_path = "results/SMS_";
	result_path = "results/";
	//TString result_path = "condor/hadd/v2/";
	TString full_or_fast = "_fullsim"; 
	//full_or_fast = "_fastsim"; 

	//TString signal_name = "T2fbd_test";
	//TString signal_name = "T2tt_test";
	TString signal_name = "T2tt_and_T1tttt_high";
	//TString signal_name = "T2tt_only";
	//TString signal_name = "T2bt_and_T2bw";
	//TString signal_name = "T1tttt_and_T5ttcc";
	//TString signal_name = "T2fbd_and_T2bwC";
	//TString signal_name = "T2cc_and_T2tt";

	TString data_name = "SingleMuon";

	bool plot_recoZpt = false;
	bool plot_recoZM = false;
	bool plot_met = false;
	bool plot_ht = false;
	bool plot_Stop0l_nJets = false;
	bool plot_lep1pT = false;
	bool plot_lep2pT = false;
	bool plot_lep3pT = true;

	float xmin =0, xmax = 800, ymin = 0, ymax = 35000, sig_ymax = 1;
	int hs_tot = 1, hs_tot_plot = 1;
	float padup_height = 0.3, padup_margin = 0, leg_height = 0.5;
	if(!plot_sig_pad) {padup_height = 0; padup_margin = 0.1, leg_height = 0.6;}
	if(plot_log) ymin = 0.1;

	TString title = "MET";
	TString var = "met_h";
	TString folder = "";

	int rebin = 1;

	if (plot_recoZpt)
	{
		title = "Reconstructed Z pT";
		var = "h_recoZpt";
		folder = "";
		rebin = 1;
		ymin = 1;
		ymax = 1000;
	}
	if (plot_recoZM)
	{
		title = "Reconstructed Z Mass";
		var = "h_recoZM";
		folder = "";
		rebin = 1;
		ymin = 1;
		ymax = 10000;
	}
	if (plot_met)
	{
		title = "MET";
		var = "h_met";
		folder = "";
		rebin = 1;
		xmax = 500;
		ymin = 1;
		ymax = 10000;
	}
	if (plot_ht)
	{
		title = "HT";
        var = "h_ht";
        folder = "";
        rebin = 1;
        ymin = 1;
        ymax = 100000;
	}
	if (plot_Stop0l_nJets)
	{
		title = "nJets";
		var = "h_Stop0l_nJets";
		folder = "";
		rebin = 1;
		ymin = 1;
		ymax = 10000000;
	}
	if(plot_lep1pT)
	{
		title = "pT of Leading Lepton in Reconstructed Z";
		var = "h_lep1pT";
		folder = "";
		rebin = 1;
		ymin = 1;
		ymax = 1000;
	}
    if(plot_lep2pT)
    {
        title = "pT of Non-Leading Lepton in Reconstructed Z";
        var = "h_lep2pT";
        folder = "";
        rebin = 1;
        ymin = 1;
        ymax = 1000;
    }
    if(plot_lep3pT)
    {
        title = "pT of Third Lepton";
        var = "h_lep3pT";
        folder = "";
        rebin = 1;
        ymin = 1;
        ymax = 1000;
    }


	TCanvas* mycanvas = new TCanvas("mycanvas", "mycanvas", 600, 600);
	//TCanvas* mycanvas = new TCanvas();
	gStyle->SetOptStat(kFALSE);

	TLegend* leg = new TLegend(0.4,leg_height,0.9,0.89);
	leg->SetBorderSize(0);
	leg->SetTextSize(0.04);

	TPad *padup = new TPad("padup", "padup", 0, padup_height, 1, 1.0);
	padup -> SetBottomMargin(padup_margin);
	padup -> Draw();
	padup -> cd();

	if (plot_log) gPad-> SetLogy();

	THStack *hs = new THStack();


	if (plot_BG)
	{
		TH1D * pro = NULL;

		if (true)
		{
			TString sp = "QCD_HT_2000toInf";

			TFile *f1 = new TFile("results/" + sp + year + ".root");
			TH1D *h1 = (TH1D*)f1->Get(folder + var);
			//TH1D *h2 = (TH1D*)f1->Get(folder + "/eff_h");
			TH1D *h2 = (TH1D*)f1->Get("Baseline_Only/eff_h");

			if(use_original_title) title = h1->GetTitle();

			double all_events = h2->GetBinContent(1);
			double left_events = h2->GetBinContent(2);

			h1->Sumw2();
			h1->Rebin(rebin);

			std::cout << sp << std::endl;
			std::cout << "unscale bin 1 content " << h1->GetBinContent(1) << std::endl;
			std::cout << "unscale bin 2 content " << h1->GetBinContent(2) << std::endl;
			std::cout << "unscale bin 1 error " << h1->GetBinError(1) << std::endl;
			std::cout << "unscale bin 2 error " << h1->GetBinError(2) << std::endl;

			h1->Scale(lumi * CrossSection.at(sp) * 1000 / all_events );
			//h1->Scale(lumi * 1000);

			std::cout << "scaled bin 1 content " << h1->GetBinContent(1) << std::endl;
			std::cout << "scaled bin 2 content " << h1->GetBinContent(2) << std::endl;
			std::cout << "scaled bin 1 error " << h1->GetBinError(1) << std::endl;
			std::cout << "scaled bin 2 error " << h1->GetBinError(2) << std::endl;

			pro = (TH1D*)h1->Clone("QCD");
		}

		if (false)
		{
			TString sp = "QCD_HT_200to300";
			Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kRed, pro, rebin);
		}

		if (true)
		{
			TString sp = "QCD_HT_300to500";
			Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kRed, pro, rebin);
		}

		if (true)
		{
			TString sp = "QCD_HT_500to700";
			Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kRed, pro, rebin);
		}

		if (true)
		{
			TString sp = "QCD_HT_700to1000";
			Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kRed, pro, rebin);
		}

		if (true)
		{
			TString sp = "QCD_HT_1000to1500";
			Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kRed, pro, rebin);
		}

		if (true)
		{
			TString sp = "QCD_HT_1500to2000";
			Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kRed, pro, rebin);
		}

		pro->SetLineColor(kBlack);
		//pro->SetLineWidth(3);
		//pro->Draw("bsame");
		pro->SetFillColor(kRed);
		leg->AddEntry(pro,"QCD","f");

		hs->Add(pro);
	}

	if (plot_BG)
	{
		TH1D * pro = NULL;

		if (true)
		{
			TString sp = "ZJetsToNuNu_HT_100to200";

			TFile *f1 = new TFile("results/" + sp + year + ".root");
			TH1D *h1 = (TH1D*)f1->Get(folder + var);
			//TH1D *h2 = (TH1D*)f1->Get(folder + "/eff_h");
			TH1D *h2 = (TH1D*)f1->Get("Baseline_Only/eff_h");

			double all_events = h2->GetBinContent(1);
			double left_events = h2->GetBinContent(2);

			h1->Sumw2();
			h1->Rebin(rebin);

			std::cout << sp << std::endl;
			std::cout << "unscale bin 1 content " << h1->GetBinContent(1) << std::endl;
			std::cout << "unscale bin 2 content " << h1->GetBinContent(2) << std::endl;
			std::cout << "unscale bin 1 error " << h1->GetBinError(1) << std::endl;
			std::cout << "unscale bin 2 error " << h1->GetBinError(2) << std::endl;

			h1->Scale(lumi * CrossSection.at(sp) * 1000 / all_events );
			//h1->Scale(lumi * 1000);

			std::cout << "scaled bin 1 content " << h1->GetBinContent(1) << std::endl;
			std::cout << "scaled bin 2 content " << h1->GetBinContent(2) << std::endl;
			std::cout << "scaled bin 1 error " << h1->GetBinError(1) << std::endl;
			std::cout << "scaled bin 2 error " << h1->GetBinError(2) << std::endl;

			pro = (TH1D*)h1->Clone("zjets");
		}

		if (true)
		{
			TString sp = "ZJetsToNuNu_HT_200to400";
			Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kGreen, pro, rebin);
		}

		if (true)
		{
			TString sp = "ZJetsToNuNu_HT_400to600";
			Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kGreen, pro, rebin);
		}

		if (true)
		{
			TString sp = "ZJetsToNuNu_HT_600to800";
			Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kGreen, pro, rebin);
		}

		if (true)
		{
			TString sp = "ZJetsToNuNu_HT_800to1200";
			Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kGreen, pro, rebin);
		}

		if (true)
		{
			TString sp = "ZJetsToNuNu_HT_1200to2500";
			Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kGreen, pro, rebin);
		}

		if (true)
		{
			TString sp = "ZJetsToNuNu_HT_2500toInf";
			Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kGreen, pro, rebin);
		}

		pro->SetLineColor(kBlack);
		//pro->SetLineWidth(3);
		//pro->Draw("bsame");
		pro->SetFillColor(kViolet-6);
		leg->AddEntry(pro,"z+jets","f");
		std::cout << "zinv total ====================================== " << pro->Integral() << std::endl;

		hs->Add(pro);
	}

	if (plot_BG)
	{
		TH1D * pro = NULL;

		if (true)
		{
			TString sp = "WJetsToLNu_HT_100to200";

			TFile *f1 = new TFile("results/" + sp + year + ".root");
			TH1D *h1 = (TH1D*)f1->Get(folder + var);
			//TH1D *h2 = (TH1D*)f1->Get(folder + "/eff_h");
			TH1D *h2 = (TH1D*)f1->Get("Baseline_Only/eff_h");

			double all_events = h2->GetBinContent(1);
			double left_events = h2->GetBinContent(2);

			h1->Sumw2();
			h1->Rebin(rebin);

			std::cout << sp << std::endl;
			std::cout << "unscale bin 1 content " << h1->GetBinContent(1) << std::endl;
			std::cout << "unscale bin 2 content " << h1->GetBinContent(2) << std::endl;
			std::cout << "unscale bin 1 error " << h1->GetBinError(1) << std::endl;
			std::cout << "unscale bin 2 error " << h1->GetBinError(2) << std::endl;

			h1->Scale(lumi * CrossSection.at(sp) * 1000 / all_events );
			//h1->Scale(lumi * 1000);

			std::cout << "scaled bin 1 content " << h1->GetBinContent(1) << std::endl;
			std::cout << "scaled bin 2 content " << h1->GetBinContent(2) << std::endl;
			std::cout << "scaled bin 1 error " << h1->GetBinError(1) << std::endl;
			std::cout << "scaled bin 2 error " << h1->GetBinError(2) << std::endl;

			pro = (TH1D*)h1->Clone("wjets");
		}

		if (false)
		{
			TString sp = "WJetsToLNu_HT_70to100";
			Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kGreen, pro, rebin);
		}

		if (true)
		{
			TString sp = "WJetsToLNu_HT_200to400";
			Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kGreen, pro, rebin);
		}

		if (true)
		{
			TString sp = "WJetsToLNu_HT_400to600";
			Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kGreen, pro, rebin);
		}

		if (true)
		{
			TString sp = "WJetsToLNu_HT_600to800";
			Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kGreen, pro, rebin);
		}

		if (true)
		{
			TString sp = "WJetsToLNu_HT_800to1200";
			Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kGreen, pro, rebin);
		}

		if (true)
		{
			TString sp = "WJetsToLNu_HT_1200to2500";
			Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kGreen, pro, rebin);
		}

		if (true)
		{
			TString sp = "WJetsToLNu_HT_2500toInf";
			Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kGreen, pro, rebin);
		}

		pro->SetLineColor(kBlack);
		//pro->SetLineWidth(3);
		//pro->Draw("bsame");
		pro->SetFillColor(kGreen);
		leg->AddEntry(pro,"w+jets","f");

		hs->Add(pro);
	}

    if (false)
    {
        TH1D * pro = NULL;

        if (true)
        {
            TString sp = "GJets_HT_100To200";

            TFile *f1 = new TFile("results/" + sp + year + ".root");
            TH1D *h1 = (TH1D*)f1->Get(folder + var);
            //TH1D *h2 = (TH1D*)f1->Get(folder + "/eff_h");
            TH1D *h2 = (TH1D*)f1->Get("Baseline_Only/eff_h");

            double all_events = h2->GetBinContent(1);
            double left_events = h2->GetBinContent(2);

            h1->Sumw2();
            h1->Rebin(rebin);

            std::cout << sp << std::endl;
            std::cout << "unscale bin 1 content " << h1->GetBinContent(1) << std::endl;
            std::cout << "unscale bin 2 content " << h1->GetBinContent(2) << std::endl;
            std::cout << "unscale bin 1 error " << h1->GetBinError(1) << std::endl;
            std::cout << "unscale bin 2 error " << h1->GetBinError(2) << std::endl;

            h1->Scale(lumi * CrossSection.at(sp) * 1000 / all_events );
            //h1->Scale(lumi * 1000);

            std::cout << "scaled bin 1 content " << h1->GetBinContent(1) << std::endl;
            std::cout << "scaled bin 2 content " << h1->GetBinContent(2) << std::endl;
            std::cout << "scaled bin 1 error " << h1->GetBinError(1) << std::endl;
            std::cout << "scaled bin 2 error " << h1->GetBinError(2) << std::endl;

            pro = (TH1D*)h1->Clone("gjets");
        }

        if (true)
        {
            TString sp = "GJets_HT_200To400";
            Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kGreen, pro, rebin);
        }

        if (true)
        {
            TString sp = "GJets_HT_400To600";
            Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kGreen, pro, rebin);
        }

        if (true)
        {
            TString sp = "GJets_HT_600ToInf";
            Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kGreen, pro, rebin);
        }


        pro->SetLineColor(kBlack);
        //pro->SetLineWidth(3);
        //pro->Draw("bsame");
        pro->SetFillColor(kYellow+2);
        leg->AddEntry(pro,"gamma+jets","f");

        hs->Add(pro);
    }


	if (plot_BG)
	{
		TH1D * pro = NULL;

		if (true)
		{
			TString sp = "TTbarSingleLepT";

			TFile *f1 = new TFile("results/" + sp + year + ".root");
			TH1D *h1 = (TH1D*)f1->Get(folder + var);
			//TH1D *h2 = (TH1D*)f1->Get(folder + "/eff_h");
			TH1D *h2 = (TH1D*)f1->Get("Baseline_Only/eff_h");

			double all_events = h2->GetBinContent(1);
			double left_events = h2->GetBinContent(2);

			h1->Sumw2();
			h1->Rebin(rebin);

			std::cout << sp << std::endl;
			std::cout << "unscale bin 1 content " << h1->GetBinContent(1) << std::endl;
			std::cout << "unscale bin 2 content " << h1->GetBinContent(2) << std::endl;
			std::cout << "unscale bin 1 error " << h1->GetBinError(1) << std::endl;
			std::cout << "unscale bin 2 error " << h1->GetBinError(2) << std::endl;

			h1->Scale(lumi * CrossSection.at(sp) * 1000 / all_events );
			//h1->Scale(lumi * 1000);

			std::cout << "scaled bin 1 content " << h1->GetBinContent(1) << std::endl;
			std::cout << "scaled bin 2 content " << h1->GetBinContent(2) << std::endl;
			std::cout << "scaled bin 1 error " << h1->GetBinError(1) << std::endl;
			std::cout << "scaled bin 2 error " << h1->GetBinError(2) << std::endl;

			pro = (TH1D*)h1->Clone("ttbar");
		}

		if (true)
		{
			TString sp = "TTbarSingleLepTbar";
			Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kGreen, pro, rebin);
		}

		if (true)
		{
			TString sp = "TTbarDiLep";
			Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kGreen, pro, rebin);
		}

        pro->SetLineColor(kBlack);
        //pro->SetLineWidth(3);
        //pro->Draw("bsame");
        pro->SetFillColor(kYellow);
        leg->AddEntry(pro,"ttbar","f");

        hs->Add(pro);
    }

    if (plot_BG)
    {
        TH1D * pro = NULL;

        if (true)
        {
            TString sp = "ST_s_lep";

            TFile *f1 = new TFile("results/" + sp + year + ".root");
            TH1D *h1 = (TH1D*)f1->Get(folder + var);
            //TH1D *h2 = (TH1D*)f1->Get(folder + "/eff_h");
            TH1D *h2 = (TH1D*)f1->Get("Baseline_Only/eff_h");

            double all_events = h2->GetBinContent(1);
            double left_events = h2->GetBinContent(2);

            h1->Sumw2();
            h1->Rebin(rebin);

            std::cout << sp << std::endl;
            std::cout << "unscale bin 1 content " << h1->GetBinContent(1) << std::endl;
            std::cout << "unscale bin 2 content " << h1->GetBinContent(2) << std::endl;
            std::cout << "unscale bin 1 error " << h1->GetBinError(1) << std::endl;
            std::cout << "unscale bin 2 error " << h1->GetBinError(2) << std::endl;

            h1->Scale(lumi * CrossSection.at(sp) * 1000 / all_events );
            //h1->Scale(lumi * 1000);

            std::cout << "scaled bin 1 content " << h1->GetBinContent(1) << std::endl;
            std::cout << "scaled bin 2 content " << h1->GetBinContent(2) << std::endl;
            std::cout << "scaled bin 1 error " << h1->GetBinError(1) << std::endl;
            std::cout << "scaled bin 2 error " << h1->GetBinError(2) << std::endl;

            pro = (TH1D*)h1->Clone("st_s_lep");
        }

        if (true)
        {
            TString sp = "ST_t_antitop";
            Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kGreen, pro, rebin);
        }

        if (true)
        {
            TString sp = "ST_t_top";
            Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kGreen, pro, rebin);
        }

		if (true)
		{
			TString sp = "ST_tW_antitop_incl";
			Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kGreen, pro, rebin);
		}

		if (true)
		{
			TString sp = "ST_tW_top_incl";
			Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kGreen, pro, rebin);
		}

        pro->SetLineColor(kBlack);
        //pro->SetLineWidth(3);
        //pro->Draw("bsame");
        pro->SetFillColor(kBlue);
        leg->AddEntry(pro,"single t","f");

        hs->Add(pro);
    }

    if (plot_BG)
    {
        TH1D * pro = NULL;

        if (true)
        {
            TString sp = "TTZToLLNuNu";

            TFile *f1 = new TFile("results/" + sp + year + ".root");
            TH1D *h1 = (TH1D*)f1->Get(folder + var);
            //TH1D *h2 = (TH1D*)f1->Get(folder + "/eff_h");
            TH1D *h2 = (TH1D*)f1->Get("Baseline_Only/eff_h");

            double all_events = h2->GetBinContent(1);
            double left_events = h2->GetBinContent(2);

            h1->Sumw2();
            h1->Rebin(rebin);

            std::cout << sp << std::endl;
            std::cout << "unscale bin 1 content " << h1->GetBinContent(1) << std::endl;
            std::cout << "unscale bin 2 content " << h1->GetBinContent(2) << std::endl;
            std::cout << "unscale bin 1 error " << h1->GetBinError(1) << std::endl;
            std::cout << "unscale bin 2 error " << h1->GetBinError(2) << std::endl;

            h1->Scale(lumi * CrossSection.at(sp) * 1000 / all_events );
            //h1->Scale(lumi * 1000);

            std::cout << "scaled bin 1 content " << h1->GetBinContent(1) << std::endl;
            std::cout << "scaled bin 2 content " << h1->GetBinContent(2) << std::endl;
            std::cout << "scaled bin 1 error " << h1->GetBinError(1) << std::endl;
            std::cout << "scaled bin 2 error " << h1->GetBinError(2) << std::endl;

            pro = (TH1D*)h1->Clone("ttztollnunu");
        }

		if (true)
		{
			TString sp = "TTZToQQ";
			Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kGreen, pro, rebin);
		}

		pro->SetLineColor(kBlack);
		//pro->SetLineWidth(3);
		//pro->Draw("bsame");
		pro->SetFillColor(kViolet);
		leg->AddEntry(pro,"ttz","f");

		hs->Add(pro);
	}

    if (plot_BG)
    {
        TH1D * pro = NULL;

        if (true)
        {
            TString sp = "DYJetsToLL_HT_70to100";

            TFile *f1 = new TFile("results/" + sp + year + ".root");
            TH1D *h1 = (TH1D*)f1->Get(folder + var);
            //TH1D *h2 = (TH1D*)f1->Get(folder + "/eff_h");
            TH1D *h2 = (TH1D*)f1->Get("Baseline_Only/eff_h");

            if(use_original_title) title = h1->GetTitle();

            double all_events = h2->GetBinContent(1);
            double left_events = h2->GetBinContent(2);

            h1->Sumw2();
            h1->Rebin(rebin);

            std::cout << sp << std::endl;
            std::cout << "unscale bin 1 content " << h1->GetBinContent(1) << std::endl;
            std::cout << "unscale bin 2 content " << h1->GetBinContent(2) << std::endl;
            std::cout << "unscale bin 1 error " << h1->GetBinError(1) << std::endl;
            std::cout << "unscale bin 2 error " << h1->GetBinError(2) << std::endl;

            h1->Scale(lumi * CrossSection.at(sp) * 1000 / all_events );
            //h1->Scale(lumi * 1000);

            std::cout << "scaled bin 1 content " << h1->GetBinContent(1) << std::endl;
            std::cout << "scaled bin 2 content " << h1->GetBinContent(2) << std::endl;
            std::cout << "scaled bin 1 error " << h1->GetBinError(1) << std::endl;
            std::cout << "scaled bin 2 error " << h1->GetBinError(2) << std::endl;

            pro = (TH1D*)h1->Clone("DY");
        }

        if (true)
        {
            TString sp = "DYJetsToLL_HT_100to200";
            Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kOrange+1, pro, rebin);
        }
        if (true)
        {
            TString sp = "DYJetsToLL_HT_200to400";
            Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kOrange+1, pro, rebin);
        }
        if (true)
        {
            TString sp = "DYJetsToLL_HT_400to600";
            Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kOrange+1, pro, rebin);
        }
        if (true)
        {
            TString sp = "DYJetsToLL_HT_600to800";
            Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kOrange+1, pro, rebin);
        }
        if (true)
        {
            TString sp = "DYJetsToLL_HT_800to1200";
            Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kOrange+1, pro, rebin);
        }
        if (true)
        {
            TString sp = "DYJetsToLL_HT_1200to2500";
            Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kOrange+1, pro, rebin);
        }
        if (true)
        {
            TString sp = "DYJetsToLL_HT_2500toInf";
            Plot_1D_AUX_bg (lumi, sp, year, var, folder, leg, kOrange+1, pro, rebin);
        }


        pro->SetLineColor(kBlack);
        //pro->SetLineWidth(3);
        //pro->Draw("bsame");
        pro->SetFillColor(kOrange+1);
        leg->AddEntry(pro,"DY","f");

        hs->Add(pro);
    }
	if(plot_BG)
	{
		hs->SetMinimum(ymin);
		if(ymax == -1) ymax = hs-> GetMaximum() * 1.2; 
		hs->SetMaximum(ymax);
		hs->Draw("hist");

		//hs->SetTitle("");
		hs->GetYaxis()->SetTitle("events");
		hs->GetXaxis()->SetRangeUser(xmin,xmax);
		hs->GetYaxis()->SetRangeUser(ymin,ymax);
		hs->GetXaxis()->SetTitle(title);
		hs->GetYaxis()->SetTitleSize(0.045);
		hs->GetYaxis()->SetTitleOffset(1.2);

		if(plot_BG)
		{
			hs_tot = ((TH1D*)(hs -> GetStack() -> Last())) -> Integral();
			int bin_xmin = ((TH1D*)(hs -> GetStack() -> Last())) -> FindBin(xmin);
			int bin_xmax = ((TH1D*)(hs -> GetStack() -> Last())) -> FindBin(xmax);
			hs_tot_plot = ((TH1D*)(hs -> GetStack() -> Last())) -> Integral(bin_xmin,bin_xmax);
			double hs_bin1 = ((TH1D*)(hs -> GetStack() -> Last())) -> GetBinContent(1);
			double hs_bin2 = ((TH1D*)(hs -> GetStack() -> Last())) -> GetBinContent(2);
			std::cout << "\ntotal BG = " << hs_tot << " bin 1 = " << hs_bin1 << " bin 2 = " << hs_bin2 << "\n" << std::endl;
			//int n_bins = 80/rebin;
			//TH1D *significance = new TH1D ("significance", "significance", n_bins, xmin, xmax);
		}
	}

	TString sp;
	double signal_scale = lumi;
	if(sig_scale_to_BG) signal_scale = hs_tot_plot; 

	if (true)
	{
		if(data_name == "SingleMuon") sp = "Data_SingleMuon";
		
		TFile *f1 = new TFile(result_path + sp + year + ".root");
		TH1D *h1 = (TH1D*)f1->Get(folder + var);
		TH1D *h2 = (TH1D*)f1->Get("Baseline_Only/eff_h");
		
		double all_events  = h2->GetBinContent(1);
		double left_events = h2->GetBinContent(2);

		std::cout << "left_events = " << left_events << std::endl;
		std::cout << "GetEntries  = " << h1->GetEntries() << std::endl;
		std::cout << "GetIntegral = " << h1->Integral() << std::endl;
		std::cout << "all_events  = " << all_events << std::endl;

		h1->Rebin(rebin);
		h1->SetLineColor(kBlack);
		h1->SetLineWidth(2);

        //if(plot_BG) h1->Draw("hist same");
		if(plot_BG) h1->Draw("same P L E"); //Add "TEXT" for written number vals. P: point; L: horiz. line; E: error bars
        else
        {
            h1->SetMinimum(ymin);
            h1->SetMaximum(ymax);
            h1->Draw("hist");

            h1->SetTitle("");
            h1->GetYaxis()->SetTitle("events");
            h1->GetXaxis()->SetRangeUser(xmin,xmax);
            h1->GetYaxis()->SetRangeUser(ymin,ymax);
            h1->GetXaxis()->SetTitle(title);
            h1->GetYaxis()->SetTitleSize(0.045);
            h1->GetYaxis()->SetTitleOffset(1.2);
        }
        leg->AddEntry(h1,sp,"l");
	}

	if (false)
	{
		if(signal_name == "T2fbd_test") sp = "T2fbd_mStop600_mLSP520";
		if(signal_name == "T2tt_test") sp = "T2tt_mStop1000_mLSP50";
		if(signal_name == "T1tttt_and_T5ttcc") sp = "T1tttt_mGluino1200_mLSP800";
		if(signal_name == "T2tt_and_T1tttt_high") sp = "T2tt_mStop1000_mLSP500";
		if(signal_name == "T2tt_only") sp = "T2tt_mStop425_mLSP325";
		if(signal_name == "T2bt_and_T2bw") sp = "T2bt_mStop500_mLSP300";
		if(signal_name == "T2fbd_and_T2bwC") sp = "T2fbd_mStop500_mLSP490";
		if(signal_name == "T2cc_and_T2tt") sp = "T2cc_mStop500_mLSP490";

		TFile *f1 = new TFile(result_path + sp + full_or_fast + year + ".root");
		TH1D *h1 = (TH1D*)f1->Get(folder + var);
		//TH1D *h2 = (TH1D*)f1->Get(folder + "/eff_h");
		TH1D *h2 = (TH1D*)f1->Get("Baseline_Only/eff_h");
		//TH1D *h3 = (TH1D*)f1.Get("mt2_uc_h");

		double all_events = h2->GetBinContent(1);
		double left_events = h2->GetBinContent(2);

		std::cout << "left_events = " << left_events << std::endl;
		std::cout << "GetEntries = " << h1->GetEntries() << std::endl;
		std::cout << "GetIntegral = " << h1->Integral() << std::endl;
		std::cout << "all_events = " << all_events << std::endl;
		//std::cout << "GetEntries = " << h3->GetEntries() << std::endl;
		//std::cout << sp << " Xsec = " << CrossSection.at(sp) << std::endl;

		if(sig_scale_to_BG) h1->Scale(signal_scale / h1->Integral() );
		else h1->Scale(signal_scale * 50 * 1000);
		//h1->Scale(signal_scale * CrossSection.at(sp) * 1000 / all_events );

		std::cout << "events rebin= " << h1->Integral()  << std::endl;

		h1->Rebin(rebin);
		h1->SetLineColor(kRed);
		h1->SetLineWidth(2);
		if(plot_BG) h1->Draw("hist same");
		else{
			h1->SetMinimum(ymin);
			h1->SetMaximum(ymax);
			h1->Draw("hist");

			h1->SetTitle("");
			h1->GetYaxis()->SetTitle("events");
			h1->GetXaxis()->SetRangeUser(xmin,xmax);
			h1->GetYaxis()->SetRangeUser(ymin,ymax);
			h1->GetXaxis()->SetTitle(title);
			h1->GetYaxis()->SetTitleSize(0.045);
			h1->GetYaxis()->SetTitleOffset(1.2);
		}
		leg->AddEntry(h1,sp,"l");
	}

	if (false)
	{
		if(signal_name == "T2fbd_test") sp = "T2fbd_mStop600_mLSP590";
		if(signal_name == "T2tt_test") sp = "T2tt_mStop1000_mLSP500";
		if(signal_name == "T1tttt_and_T5ttcc") sp = "T1tttt_mGluino1500_mLSP100";
		if(signal_name == "T2tt_and_T1tttt_high") sp = "T2tt_mStop1000_mLSP1";
		if(signal_name == "T2tt_only") sp = "T2tt_mStop500_mLSP325";
		if(signal_name == "T2bt_and_T2bw") sp = "T2bt_mStop800_mLSP100";
		if(signal_name == "T2fbd_and_T2bwC") sp = "T2fbd_mStop600_mLSP520";
		if(signal_name == "T2cc_and_T2tt") sp = "T2cc_mStop500_mLSP420";
		Plot_1D_AUX_sg (signal_scale, result_path, sp, full_or_fast, year, var, folder, leg, kGreen, rebin, sig_scale_to_BG);
	}

	if (false)
	{
		if(signal_name == "T1tttt_and_T5ttcc") sp = "T5ttcc_mGluino1000_mLSP800";
		if(signal_name == "T2tt_and_T1tttt_high") sp = "T1tttt_mGluino2000_mLSP1000";
		if(signal_name == "T2tt_only") sp = "T2tt_mStop850_mLSP350";
		if(signal_name == "T2bt_and_T2bw") sp = "T2bw_mStop500_mLSP325";
		if(signal_name == "T2fbd_and_T2bwC") sp = "T2bwC_mStop500_mLSP490";
		if(signal_name == "T2cc_and_T2tt") sp = "T2tt_mStop250_mLSP150";
		Plot_1D_AUX_sg (signal_scale, result_path, sp, full_or_fast, year, var, folder, leg, kGreen, rebin, sig_scale_to_BG);
	}

	if (false)
	{
		if(signal_name == "T1tttt_and_T5ttcc") sp = "T5ttcc_mGluino1500_mLSP100";
		if(signal_name == "T2tt_and_T1tttt_high") sp = "T1tttt_mGluino2000_mLSP100";
		if(signal_name == "T2tt_only") sp = "T2tt_mStop850_mLSP100";
		if(signal_name == "T2bt_and_T2bw") sp = "T2bw_mStop800_mLSP100";
		if(signal_name == "T2fbd_and_T2bwC") sp = "T2bwC_mStop600_mLSP520";
		if(signal_name == "T2cc_and_T2tt") sp = "T2tt_mStop425_mLSP325";
		Plot_1D_AUX_sg (signal_scale, result_path, sp, full_or_fast, year, var, folder, leg, kGreen, rebin, sig_scale_to_BG);
	}

	TLatex latex;
	latex.SetTextSize(0.04);
	latex.SetNDC();
	//latex.SetTextAlign(13);  //align at top
	//latex.DrawLatex(0.5,ymax+0.4,"#bf{CMS} Preliminary, 2017 data");
	latex.DrawLatex(0.1,0.91,"CMS #bf{Simulation}");
	TString lumi_and_energy = "#bf{" + std::to_string((int)lumi) + " fb^{-1} (13TeV)}";
	if(plot_BG) latex.DrawLatex(0.74,0.91,lumi_and_energy);
	else latex.DrawLatex(0.80,0.91,"#bf{13TeV}");
	TString sig_scale = "#splitline{signals scaled to}{BG sum =" + std::to_string(hs_tot_plot) + "}";
	if(plot_BG)
	{
		//if(sig_scale_to_BG) latex.DrawLatex(0.12,0.82,"#bf{signals scaled to BG sum}");
		//if(sig_scale_to_BG) latex.DrawLatex(0.12,0.82,sig_scale);
		//else latex.DrawLatex(0.12,0.85,"#bf{signals scaled up X50}");
	}

	leg->Draw("same");

	if(plot_sig_pad)
	{
		mycanvas -> cd();

		TPad *paddown = new TPad("paddown", "paddown", 0, 0, 1, 0.3);
		paddown -> SetTopMargin(0);
		paddown -> SetBottomMargin(0.3);
		paddown -> SetGrid();
		paddown -> Draw();
		paddown -> cd();

		if (true)
		{
			if(data_name == "SingleMuon") sp = "Data_SingleMuon";

			TFile *f1 = new TFile(result_path + sp + year + ".root");
			TH1D *h1 = (TH1D*)f1->Get(folder + var);
			TH1D *h2 = (TH1D*)f1->Get("Baseline_Only/eff_h");

			double all_events = h2->GetBinContent(1);
			double left_events = h2->GetBinContent(2);

			h1->Sumw2();
			h1->Rebin(rebin);

			TH1D *ratio = (TH1D*)h1->Clone("ratio");
			int n_bins = ratio->GetSize() - 2;

			std::cout << "\n" << sp << std::endl;

            for (int i = 1; i <= n_bins; i++)
            {
                double data = h1->GetBinContent(i);
                double back_ground = ((TH1D*)(hs -> GetStack() -> Last())) -> GetBinContent(i);
                if (back_ground < 0) back_ground = 0;
				if (back_ground != 0)
				{
					double data_bg_ratio = data / back_ground;
					ratio -> SetBinContent(i,data_bg_ratio);
				}
                //double signal_uc = sqrt (pow(h1->GetBinError(i),2) + pow(0.16*signal,2));  //signal sys unc = 16%
                //double back_ground_uc = sqrt (pow(((TH1D*)(hs -> GetStack() -> Last())) -> GetBinError(i),2) + pow(0.2*back_ground,2));  //bg sys unc = 20%
                //if (back_ground == 0) back_ground_uc = 1.8;  //unc for empty bin is [0,1.8]
                //double sigma = signal + back_ground + signal_uc*signal_uc + back_ground_uc*back_ground_uc;
                //double ratio = 0;
                //if (sigma > 0) ratio = signal / sqrt(sigma);
                //double minus = 2 * sqrt (sigma) - 2 * sqrt (back_ground + back_ground_uc*back_ground_uc);
                //if (use_low_stat_sig) significance->SetBinContent(i,minus);
                //else significance->SetBinContent(i,ratio);

                std::cout << "bin " << i << " data = " << data << " BG = " << back_ground << " ratio = " << ratio->GetBinContent(i) << std::endl;
            }

            ratio->SetTitle("");
            ratio->GetYaxis()->SetTitle("ratio");
            ratio->GetXaxis()->SetRangeUser(xmin,xmax);
            ratio->GetXaxis()->SetTitle(title);
            ratio->GetXaxis()->SetTitleSize(0.1);
            ratio->GetXaxis()->SetLabelSize(0.08);
            ratio->GetYaxis()->SetTitleOffset(0.5);
            ratio->GetYaxis()->SetTitleSize(0.1);
            ratio->GetYaxis()->SetLabelSize(0.08);

            //ratio->SetMaximum(sig_ymax);
			//ratio->SetMaximum(1);
            //ratio->SetLineColor(kRed);
            ratio->SetLineColor(kBlack);
            ratio->SetLineWidth(2);
            ratio->Draw("hist");
            //ratio->Draw("PLE");
            //leg->AddEntry(h1,sp,"l");
		}

		if (false)
		{
			if(signal_name == "T2fbd_test") sp = "T2fbd_mStop600_mLSP520";
			if(signal_name == "T2tt_test") sp = "T2tt_mStop1000_mLSP50";
			if(signal_name == "T1tttt_and_T5ttcc") sp = "T1tttt_mGluino1200_mLSP800";
			if(signal_name == "T2tt_and_T1tttt_high") sp = "T2tt_mStop1000_mLSP500";
			if(signal_name == "T2tt_only") sp = "T2tt_mStop425_mLSP325";
			if(signal_name == "T2bt_and_T2bw") sp = "T2bt_mStop500_mLSP300";
			if(signal_name == "T2fbd_and_T2bwC") sp = "T2fbd_mStop500_mLSP490";
			if(signal_name == "T2cc_and_T2tt") sp = "T2cc_mStop500_mLSP490";

			TFile *f1 = new TFile(result_path + sp + full_or_fast + year + ".root");
			TH1D *h1 = (TH1D*)f1->Get(folder + var);
			//TH1D *h2 = (TH1D*)f1->Get(folder + "/eff_h");
			TH1D *h2 = (TH1D*)f1->Get("Baseline_Only/eff_h");

			double all_events = h2->GetBinContent(1);
			double left_events = h2->GetBinContent(2);
			//int n_bins = ((TH1D*)(hs -> GetStack() -> Last())) -> GetSize() - 2;
			//TH1D *significance = new TH1D ("significance", title, n_bins, xmin_h, xmax_h);

			h1->Sumw2();
			h1->Rebin(rebin);

			//h1->Scale(lumi / h1->Integral() );
			h1->Scale(lumi * CrossSection.at(sp) * 1000 / all_events );
			//h1->Scale(lumi * 1000);

			TH1D *significance = (TH1D*)h1->Clone("significance");;
			int n_bins = significance-> GetSize() - 2;

			std::cout << "\n" << sp << std::endl;

			for (int i = 1; i <= n_bins; i++)
			{
				double signal = h1->GetBinContent(i);
				double back_ground = ((TH1D*)(hs -> GetStack() -> Last())) -> GetBinContent(i);
				if (back_ground < 0) back_ground = 0;
				double signal_uc = sqrt (pow(h1->GetBinError(i),2) + pow(0.16*signal,2));  //signal sys unc = 16%
				double back_ground_uc = sqrt (pow(((TH1D*)(hs -> GetStack() -> Last())) -> GetBinError(i),2) + pow(0.2*back_ground,2));  //bg sys unc = 20%
				if (back_ground == 0) back_ground_uc = 1.8;  //unc for empty bin is [0,1.8]
				double sigma = signal + back_ground + signal_uc*signal_uc + back_ground_uc*back_ground_uc;
				double ratio = 0;
				if (sigma > 0) ratio = signal / sqrt(sigma);
				double minus = 2 * sqrt (sigma) - 2 * sqrt (back_ground + back_ground_uc*back_ground_uc);
				if (use_low_stat_sig) significance->SetBinContent(i,minus);
				else significance->SetBinContent(i,ratio);

				std::cout << "bin " << i << " signal = " << signal << " signal uc = " << signal_uc << " BG = " << back_ground << " BG unc = " << back_ground_uc << " significance = " << significance->GetBinContent(i) << std::endl;
			}

			significance->SetTitle("");
			significance->GetYaxis()->SetTitle("significance");
			significance->GetXaxis()->SetRangeUser(xmin,xmax);
			significance->GetXaxis()->SetTitle(title);
			significance->GetXaxis()->SetTitleSize(0.1);
			significance->GetXaxis()->SetLabelSize(0.08);
			significance->GetYaxis()->SetTitleOffset(0.5);
			significance->GetYaxis()->SetTitleSize(0.1);
			significance->GetYaxis()->SetLabelSize(0.08);

			significance->SetMaximum(sig_ymax);
			significance->SetLineColor(kRed);
			significance->SetLineWidth(2);
			significance->Draw("hist");
			//leg->AddEntry(h1,sp,"l");
		}

		if (false)
		{
			if(signal_name == "T2fbd_test") sp = "T2fbd_mStop600_mLSP590";
			if(signal_name == "T2tt_test") sp = "T2tt_mStop1000_mLSP500";
			if(signal_name == "T1tttt_and_T5ttcc") sp = "T1tttt_mGluino1500_mLSP100";
			if(signal_name == "T2tt_and_T1tttt_high") sp = "T2tt_mStop1000_mLSP1";
			if(signal_name == "T2tt_only") sp = "T2tt_mStop500_mLSP325";
			if(signal_name == "T2bt_and_T2bw") sp = "T2bt_mStop800_mLSP100";
			if(signal_name == "T2fbd_and_T2bwC") sp = "T2fbd_mStop600_mLSP520";
			if(signal_name == "T2cc_and_T2tt") sp = "T2cc_mStop500_mLSP420";
			Plot_1D_AUX_sig (lumi, result_path, sp, full_or_fast, year, var, folder, leg, kGreen, hs, rebin, use_low_stat_sig);
			//Plot_1D_AUX_sg (1.0, sp, var, folder, leg, kGreen, rebin);
		}

		if (false)
		{
			if(signal_name == "T1tttt_and_T5ttcc") sp = "T5ttcc_mGluino1000_mLSP800";
			if(signal_name == "T2tt_and_T1tttt_high") sp = "T1tttt_mGluino2000_mLSP1000";
			if(signal_name == "T2tt_only") sp = "T2tt_mStop850_mLSP350";
			if(signal_name == "T2bt_and_T2bw") sp = "T2bw_mStop500_mLSP325";
			if(signal_name == "T2fbd_and_T2bwC") sp = "T2bwC_mStop500_mLSP490";
			if(signal_name == "T2cc_and_T2tt") sp = "T2tt_mStop250_mLSP150";
			Plot_1D_AUX_sig (lumi, result_path, sp, full_or_fast, year, var, folder, leg, kGreen, hs, rebin, use_low_stat_sig);
			//Plot_1D_AUX_sg (1.0, sp, var, folder, leg, kYellow, rebin);
		}

		if (false)
		{
			if(signal_name == "T1tttt_and_T5ttcc") sp = "T5ttcc_mGluino1500_mLSP100";
			if(signal_name == "T2tt_and_T1tttt_high") sp = "T1tttt_mGluino2000_mLSP100";
			if(signal_name == "T2tt_only") sp = "T2tt_mStop850_mLSP100";
			if(signal_name == "T2bt_and_T2bw") sp = "T2bw_mStop800_mLSP100";
			if(signal_name == "T2fbd_and_T2bwC") sp = "T2bwC_mStop600_mLSP520";
			if(signal_name == "T2cc_and_T2tt") sp = "T2tt_mStop425_mLSP325";
			Plot_1D_AUX_sig (lumi, result_path, sp, full_or_fast, year, var, folder, leg, kGreen, hs, rebin, use_low_stat_sig);
			//Plot_1D_AUX_sg (1.0, sp, var, folder, leg, kBlue, rebin);
		}
	}

	if(use_low_stat_sig)
	{
		//mycanvas->SetLogy();
		mycanvas->SaveAs("plots/" + signal_name + "_" + var + "_use_low_stat_sig.png");
	}
	else
		mycanvas->SaveAs("plots/" + signal_name + "_" + var + ".png");

	return 0;
}
