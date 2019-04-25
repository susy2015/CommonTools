//#include "CrossSection.C"
#include "Plot_1D_AUX.c"
int Plot_1D_test()
{
	//gROOT->ForceStyle();

	const double lumi = 36;
	TString year = "_2016";
	bool plot_log = false;
	plot_log = true;
	bool plot_sig_pad = true;
	bool plot_BG = true;
	bool use_low_stat_sig = false;
	//use_low_stat_sig = true;
	bool sig_scale_to_BG = true;
	bool use_original_title = false;

	TString result_path = "results/Signal_";        //for full sim signals
	//result_path = "results/Signal_fastsim_";        //for fast sim singals

	TString signal_name = "T2tt_test";
	//TString signal_name = "T2tt_and_T1tttt_high";
	//TString signal_name = "T2tt_only";
	//TString signal_name = "T2bt_and_T2bw";
	//TString signal_name = "T1tttt_and_T5ttcc";
	//TString signal_name = "T2fbd_and_T2bwC";
	//TString signal_name = "T2cc_and_T2tt";

	bool plot_MT2 = false;
	bool plot_MT2_baseline_no_mt2 = false;
	bool plot_MTb = false;
	bool plot_MTb_highdm = false;
	bool plot_MT2_b = false;
	bool plot_SB_v2 = true;
	bool plot_SB_team_A_highdm = false;
	bool plot_SB_team_A_lowdm = false;
	bool plot_nbottompt20 = false;
	bool plot_nbottompt20_lowdm = false;
	bool plot_nbottompt30 = false;
	bool plot_ntop = false;
	bool plot_ntop_merge = false;
	bool plot_ntop_w = false;
	bool plot_ntop_res = false;
	bool plot_nw = false;
	bool plot_gen_w_pt = false;
	bool plot_gen_b_pt = false;
	bool plot_gen_w_b_mass = false;
	bool plot_gen_w_b_delta_r = false;
	bool plot_n_res_b_gen_match = false;
	bool plot_n_res_w_gen_match = false;
	bool plot_n_res_gen_match = false;
	bool plot_njetspt20 = false;
	bool plot_njetspt20_lowdm = false;
	bool plot_njetspt30 = false;
	bool plot_nSV_lowdm = false;
	bool plot_HT = false;
	bool plot_MET = false;
	bool plot_MET_lowdm = false;
	bool plot_MET_binning_study = false;
	bool plot_ISR_pt_lowdm = false;
	bool plot_bottom_pt_lowdm = false;
	bool plot_MT2_different_MTb = false;
	bool plot_jpt_eta_2p5_3p0 = false;
	bool plot_jpt_eta_2p5_3p0_no_HT = false;

	float xmin =0, xmax = 800, ymin = 0, ymax = 35000, sig_ymax = 1;
	int hs_tot = 1, hs_tot_plot = 1;
	float padup_height = 0.3, padup_margin = 0, leg_height = 0.5;
	if(!plot_sig_pad) {padup_height = 0; padup_margin = 0.1, leg_height = 0.6;}
	if(plot_log) ymin = 0.1;

	TString title = "MT2";
	TString var = "mt2_h";
	TString folder = "Baseline_Only/";

	int rebin = 1;

	if (plot_MET_binning_study)
	{	
		//title = "MT2";
		//var = "mt2_h";
		title = "";
		var = "met_1b_011_h";
		folder = "";
		//rebin = 5;
		xmin = 200;
		xmax = 800;
		ymax = -1;
	}

	if (plot_MT2)
	{	
		//title = "MT2";
		//var = "mt2_h";
		title = "MT2 when MTb > 175";
		var = "mt2_high_h";
		folder = "Baseline_MTb>175/";
		rebin = 5;
		xmin = 50;
		ymax = 10000;
	}

	if (plot_MT2_baseline_no_mt2)
	{	
		title = "";
		var = "mt2_baseline_no_mt2_h";
		folder = "";
		rebin = 5;
		//xmin = 100;
		//xmax = 500;
		//ymax = 250;
		ymax = 4000;
	}

	if (plot_MTb)
	{
		title = "MTb [GeV]";
		var = "mtb_h";
		folder = "";
		rebin = 1;
		xmin = 10;
		xmax = 350;
		ymax = 10000;
		sig_ymax = 0.3;
	}

	if (plot_MTb_highdm)
	{
		title = "MTb [GeV]";
		var = "mtb_highdm_h";
		folder = "";
		rebin = 2;
		xmax = 400;
		ymax = 3000;
	}

	if (plot_MT2_b)
	{
		title = "MT2 with b";
		var = "mt2_b_h";
		rebin = 1;
		xmax = 100;
		ymax = 25000;
	}

	if (plot_SB_v2)
	{
		title = "search bin v2";
		var = "search_bin_v2_h";
		folder = "";
		rebin = 1;
		xmax = 205;
		ymax = 1000000;
		sig_ymax = 2;
	}

	if (plot_SB_team_A_highdm)
	{
		title = "high dm search bin";
		var = "search_bin_team_A_highdm_h";
		folder = "";
		rebin = 1;
		xmin = 53;
		xmax = 104;
		ymax = 10000000;
		sig_ymax = 2;
	}

	if (plot_SB_team_A_lowdm)
	{
		title = "low dm search bin";
		var = "search_bin_team_A_lowdm_h";
		folder = "";
		rebin = 1;
		xmin = 0;
		xmax = 53;
		ymax = 10000000;
		sig_ymax = 2;
	}

	if (plot_nbottompt20)
	{
		title = "number of b jets (MTb > 175 GeV)";
		var = "nbottompt20_175_h";
		folder = "";
		rebin = 1;
		xmax = 8;
		ymax = 100000;
		sig_ymax = 0.3;
	}

	if (plot_nbottompt20_lowdm)
	{
		title = "number of b jets, low dm";
		var = "nbottompt20_lowdm_h";
		folder = "";
		rebin = 1;
		xmax = 8;
		ymax = 1000000000;
		sig_ymax = 0.6;
	}

	if (plot_nbottompt30)
	{
		title = "number of b jets (MTb > 175 GeV)";
		var = "nbottompt30_175_h";
		folder = "";
		rebin = 1;
		xmax = 8;
		//ymax = 10000000;
		ymax = 100000;
		sig_ymax = 0.3;
	}

	if (plot_ntop)
	{
		title = "ntop, loose baseline";
		var = "ntop_h";
		folder = "";
		rebin = 1;
		xmax = 8;
		//ymax = 1000000;
		ymax = 30000;
		sig_ymax = 3;
	}

	if (plot_ntop_merge)
	{
		title = "number of fully merged Top (MTb > 175 GeV)";
		var = "ntop_merge_175_h";
		folder = "";
		rebin = 1;
		xmax = 8;
		//ymax = 1;
		ymax = 10000000;
		sig_ymax = 3;
	}

	if (plot_ntop_w)
	{
		title = "number of partialy merged top when MTb > 175";
		var = "ntop_w_175_h";
		folder = "";
		rebin = 1;
		xmax = 8;
		ymax = 1;
		//ymax = 35000;
		sig_ymax = 3;
	}

	if (plot_ntop_res)
	{
		title = "number of resolved Top (MTb > 175 GeV)";
		var = "ntop_res_175_h";
		folder = "";
		rebin = 1;
		xmax = 8;
		//ymax = 1;
		ymax = 10000000;
		sig_ymax = 0.6;
	}

	if (plot_nw)
	{
		title = "number of W (MTb > 175 GeV)";
		var = "nw_175_h";
		folder = "";
		rebin = 1;
		xmax = 8;
		ymax = 1000000;
		sig_ymax = 0.3;
	}

	if (plot_gen_w_pt)
	{
		title = "gen w pt when MTb > 175";
		var = "gen_w_pt_175_h";
		folder = "";
		rebin = 8;
		xmax = 400;
		ymax = 0.4;
	}

	if (plot_gen_b_pt)
	{
		title = "gen b pt when MTb > 175";
		var = "gen_b_pt_175_h";
		folder = "";
		rebin = 8;
		xmax = 400;
		ymax = 0.4;
	}

	if (plot_gen_w_b_mass)
	{
		title = "gen w and b mass when MTb > 175";
		var = "gen_w_b_mass_175_h";
		folder = "";
		rebin = 1;
		xmax = 400;
		ymax = 0.7;
	}

	if (plot_gen_w_b_delta_r)
	{
		title = "gen w and b delta R when MTb > 175";
		var = "gen_w_b_delta_r_175_h";
		folder = "";
		rebin = 8;
		xmax = 400;
		ymax = 0.6;
	}

	if (plot_n_res_gen_match)
	{
		title = "number of gen matched resolved jets when ntop = 1 and MTb > 175";
		var = "n_res_gen_match_h";
		folder = "";
		rebin = 1;
		xmax = 400;
		ymax = 0.7;
	}

	if (plot_n_res_b_gen_match)
	{
		title = "number of gen matched b in resolved jets when ntop = 1 and MTb > 175";
		var = "n_res_b_gen_match_h";
		folder = "";
		rebin = 1;
		xmax = 400;
		ymax = 0.9;
	}

	if (plot_n_res_w_gen_match)
	{
		title = "number of gen matched w in resolved jets when ntop = 1 and MTb > 175";
		var = "n_res_w_gen_match_h";
		folder = "";
		rebin = 1;
		xmax = 400;
		ymax = 0.9;
	}

	if (plot_njetspt20)
	{
		title = "number of jets (MTb > 175 GeV)";
		var = "njetspt20_175_h";
		folder = "";
		rebin = 1;
		xmax = 20;
		ymax = 40000;
		sig_ymax = 0.15;
	}

	if (plot_njetspt20_lowdm)
	{
		title = "number of jets, low dm";
		var = "njetspt20_lowdm_h";
		folder = "";
		rebin = 1;
		xmax = 20;
		ymax = 300000;
		sig_ymax = 0.3;
	}

	if (plot_njetspt30)
	{
		title = "number of jets (MTb > 175 GeV)";
		var = "njetspt30_175_h";
		folder = "";
		rebin = 1;
		xmax = 20;
		ymax = 50000;
		sig_ymax = 0.6;
	}

	if (plot_nSV_lowdm)
	{
		title = "number of soft-b jets, low dm";
		var = "nSV_lowdm_h";
		folder = "";
		rebin = 1;
		xmax = 8;
		ymax = 100000000;
		sig_ymax = 0.5;
	}

	if (plot_HT)
	{
		title = "HT (GeV) when MTb > 175";
		var = "HT_175_h";
		folder = "";
		rebin = 5;
		xmax = 3200;
		ymax = 10000;
	}

	if (plot_MET)
	{
		title = "MET [GeV] (MTb > 175 GeV)";
		var = "met_175_h";
		folder = "";
		rebin = 2;
		xmin = 250;
		xmax = 800;
		ymax = 40000;
		sig_ymax = 0.5;
	}

	if (plot_MET_lowdm)
	{
		title = "MET [GeV] low dm";
		var = "met_lowdm_h";
		folder = "";
		rebin = 2;
		xmin = 250;
		xmax = 800;
		ymax = 250000;
		sig_ymax = 1;
	}

	if (plot_ISR_pt_lowdm)
	{
		title = "ISR pt [GeV] low dm";
		var = "ISRpt_lowdm_h";
		folder = "";
		rebin = 2;
		xmax = 1000;
		ymax = 200000;
		sig_ymax = 0.8;
	}

	if (plot_bottom_pt_lowdm)
	{
		title = "bottom pt [GeV] sclar sum low dm";
		var = "bottompt_scalar_sum_lowdm_h";
		folder = "";
		rebin = 1;
		xmin = 20;
		xmax = 200;
		ymax = 20000;
		sig_ymax = 0.5;
	}

	if (plot_MT2_different_MTb)
	{
		title = "MT2 (50 - 800) when MTb > 175";
		var = "mt2_175_h";
		folder = "";
		rebin = 5;
		xmin = 50;
		ymax = 10000;
	}

	if (plot_jpt_eta_2p5_3p0)
	{
		title = "jet(2.5 < eta < 3.0) pt (GeV)";
		var = "jpt_eta_2p5_3p0_h";
		folder = "";
		rebin = 4;
		xmin = 20;
		ymax = 0.2;
	}

	if (plot_jpt_eta_2p5_3p0_no_HT)
	{
		title = "jet(2.5 < eta < 3.0) pt (GeV), no HT cut";
		var = "jpt_eta_2p5_3p0_no_HT_h";
		folder = "";
		rebin = 4;
		xmin = 20;
		ymax = 0.2;
	}

	TCanvas* mycanvas = new TCanvas("mycanvas", "mycanvas", 700, 700);
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
			TString sp = "QCD_HT2000toInf" + year;

			TFile *f1 = new TFile("results/" + sp + ".root");
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

			//h1->Scale(lumi * CrossSection.at(sp) * 1000 / all_events );
			h1->Scale(lumi * 1000);

			std::cout << "scaled bin 1 content " << h1->GetBinContent(1) << std::endl;
			std::cout << "scaled bin 2 content " << h1->GetBinContent(2) << std::endl;
			std::cout << "scaled bin 1 error " << h1->GetBinError(1) << std::endl;
			std::cout << "scaled bin 2 error " << h1->GetBinError(2) << std::endl;

			pro = (TH1D*)h1->Clone("QCD");
		}

		if (false)
		{
			TString sp = "QCD_HT200to300" + year;
			Plot_1D_AUX_bg (lumi, sp, var, folder, leg, kGreen, pro, rebin);
		}

		if (false)
		{
			TString sp = "QCD_HT300to500" + year;
			Plot_1D_AUX_bg (lumi, sp, var, folder, leg, kGreen, pro, rebin);
		}

		if (false)
		{
			TString sp = "QCD_HT500to700" + year;
			Plot_1D_AUX_bg (lumi, sp, var, folder, leg, kGreen, pro, rebin);
		}

		if (false)
		{
			TString sp = "QCD_HT700to1000" + year;
			Plot_1D_AUX_bg (lumi, sp, var, folder, leg, kGreen, pro, rebin);
		}

		if (false)
		{
			TString sp = "QCD_HT1000to1500" + year;
			Plot_1D_AUX_bg (lumi, sp, var, folder, leg, kGreen, pro, rebin);
		}

		if (true)
		{
			TString sp = "QCD_HT1500to2000" + year;
			Plot_1D_AUX_bg (lumi, sp, var, folder, leg, kGreen, pro, rebin);
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
			TString sp = "ZJetsToNuNu_HT_100to200" + year;

			TFile *f1 = new TFile("results/" + sp + ".root");
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

			//h1->Scale(lumi * CrossSection.at(sp) * 1000 / all_events );
			h1->Scale(lumi * 1000);

			std::cout << "scaled bin 1 content " << h1->GetBinContent(1) << std::endl;
			std::cout << "scaled bin 2 content " << h1->GetBinContent(2) << std::endl;
			std::cout << "scaled bin 1 error " << h1->GetBinError(1) << std::endl;
			std::cout << "scaled bin 2 error " << h1->GetBinError(2) << std::endl;

			pro = (TH1D*)h1->Clone("zjets");
		}

		if (true)
		{
			TString sp = "ZJetsToNuNu_HT_200to400" + year;
			Plot_1D_AUX_bg (lumi, sp, var, folder, leg, kGreen, pro, rebin);
		}

		if (false)
		{
			TString sp = "ZJetsToNuNu_HT_400to600" + year;
			Plot_1D_AUX_bg (lumi, sp, var, folder, leg, kGreen, pro, rebin);
		}

		if (true)
		{
			TString sp = "ZJetsToNuNu_HT_600to800" + year;
			Plot_1D_AUX_bg (lumi, sp, var, folder, leg, kGreen, pro, rebin);
		}

		if (true)
		{
			TString sp = "ZJetsToNuNu_HT_800to1200" + year;
			Plot_1D_AUX_bg (lumi, sp, var, folder, leg, kGreen, pro, rebin);
		}

		if (false)
		{
			TString sp = "ZJetsToNuNu_HT_1200to2500" + year;
			Plot_1D_AUX_bg (lumi, sp, var, folder, leg, kGreen, pro, rebin);
		}

		if (true)
		{
			TString sp = "ZJetsToNuNu_HT_2500toInf" + year;
			Plot_1D_AUX_bg (lumi, sp, var, folder, leg, kGreen, pro, rebin);
		}

		pro->SetLineColor(kBlack);
		//pro->SetLineWidth(3);
		//pro->Draw("bsame");
		pro->SetFillColor(kGreen);
		leg->AddEntry(pro,"z+jets","f");
		std::cout << "zinv total ====================================== " << pro->Integral() << std::endl;

		hs->Add(pro);
	}

	if (plot_BG)
	{
		TH1D * pro = NULL;

		if (true)
		{
			TString sp = "WJetsToLNu_HT_70to100" + year;

			TFile *f1 = new TFile("results/" + sp + ".root");
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

			//h1->Scale(lumi * CrossSection.at(sp) * 1000 / all_events );
			h1->Scale(lumi * 1000);

			std::cout << "scaled bin 1 content " << h1->GetBinContent(1) << std::endl;
			std::cout << "scaled bin 2 content " << h1->GetBinContent(2) << std::endl;
			std::cout << "scaled bin 1 error " << h1->GetBinError(1) << std::endl;
			std::cout << "scaled bin 2 error " << h1->GetBinError(2) << std::endl;

			pro = (TH1D*)h1->Clone("wjets");
		}

		if (true)
		{
			TString sp = "WJetsToLNu_HT_100to200" + year;
			Plot_1D_AUX_bg (lumi, sp, var, folder, leg, kGreen, pro, rebin);
		}

		if (true)
		{
			TString sp = "WJetsToLNu_HT_200to400" + year;
			Plot_1D_AUX_bg (lumi, sp, var, folder, leg, kGreen, pro, rebin);
		}

		if (true)
		{
			TString sp = "WJetsToLNu_HT_400to600" + year;
			Plot_1D_AUX_bg (lumi, sp, var, folder, leg, kGreen, pro, rebin);
		}

		if (true)
		{
			TString sp = "WJetsToLNu_HT_600to800" + year;
			Plot_1D_AUX_bg (lumi, sp, var, folder, leg, kGreen, pro, rebin);
		}

		if (true)
		{
			TString sp = "WJetsToLNu_HT_800to1200" + year;
			Plot_1D_AUX_bg (lumi, sp, var, folder, leg, kGreen, pro, rebin);
		}

		if (true)
		{
			TString sp = "WJetsToLNu_HT_1200to2500" + year;
			Plot_1D_AUX_bg (lumi, sp, var, folder, leg, kGreen, pro, rebin);
		}

		if (true)
		{
			TString sp = "WJetsToLNu_HT_2500toInf" + year;
			Plot_1D_AUX_bg (lumi, sp, var, folder, leg, kGreen, pro, rebin);
		}

		pro->SetLineColor(kBlack);
		//pro->SetLineWidth(3);
		//pro->Draw("bsame");
		pro->SetFillColor(kYellow);
		leg->AddEntry(pro,"w+jets","f");

		hs->Add(pro);
	}

	if (plot_BG)
	{
		TH1D * pro = NULL;

		if (true)
		{
			TString sp = "TTbarSingleLepT" + year;

			TFile *f1 = new TFile("results/" + sp + ".root");
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

			//h1->Scale(lumi * CrossSection.at(sp) * 1000 / all_events );
			h1->Scale(lumi * 1000);

			std::cout << "scaled bin 1 content " << h1->GetBinContent(1) << std::endl;
			std::cout << "scaled bin 2 content " << h1->GetBinContent(2) << std::endl;
			std::cout << "scaled bin 1 error " << h1->GetBinError(1) << std::endl;
			std::cout << "scaled bin 2 error " << h1->GetBinError(2) << std::endl;

			pro = (TH1D*)h1->Clone("ttbar");
		}

		if (true)
		{
			TString sp = "TTbarSingleLepTbar" + year;
			Plot_1D_AUX_bg (lumi, sp, var, folder, leg, kGreen, pro, rebin);
		}

		if (true)
		{
			TString sp = "TTbarDiLep" + year;
			Plot_1D_AUX_bg (lumi, sp, var, folder, leg, kGreen, pro, rebin);
		}

		if (true)
		{
			TString sp = "ST_s" + year;
			Plot_1D_AUX_bg (lumi, sp, var, folder, leg, kGreen, pro, rebin);
		}

		if (false)
		{
			TString sp = "ST_t_antitop" + year;
			Plot_1D_AUX_bg (lumi, sp, var, folder, leg, kGreen, pro, rebin);
		}

		if (true)
		{
			TString sp = "ST_t_top" + year;
			Plot_1D_AUX_bg (lumi, sp, var, folder, leg, kGreen, pro, rebin);
		}

		if (true)
		{
			TString sp = "ST_tW_antitop_incl" + year;
			Plot_1D_AUX_bg (lumi, sp, var, folder, leg, kGreen, pro, rebin);
		}

		if (true)
		{
			TString sp = "ST_tW_top_incl" + year;
			Plot_1D_AUX_bg (lumi, sp, var, folder, leg, kGreen, pro, rebin);
		}

		if (true)
		{
			TString sp = "TTZToLLNuNu" + year;
			Plot_1D_AUX_bg (lumi, sp, var, folder, leg, kGreen, pro, rebin);
		}

		if (true)
		{
			TString sp = "TTZToQQ" + year;
			Plot_1D_AUX_bg (lumi, sp, var, folder, leg, kGreen, pro, rebin);
		}

		pro->SetLineColor(kBlack);
		//pro->SetLineWidth(3);
		//pro->Draw("bsame");
		pro->SetFillColor(kViolet);
		leg->AddEntry(pro,"ttbar + single t + ttz","f");

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
		if(plot_SB_team_A_highdm || plot_SB_team_A_lowdm) hs->GetXaxis()->SetNdivisions(30);
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
		if(signal_name == "T2tt_test") sp = "T2tt_mStop850_mLSP100_fullsim" + year;
		if(signal_name == "T1tttt_and_T5ttcc") sp = "T1tttt_mGluino1200_mLSP800";
		if(signal_name == "T2tt_and_T1tttt_high") sp = "T2tt_mStop1000_mLSP500";
		if(signal_name == "T2tt_only") sp = "T2tt_mStop425_mLSP325";
		if(signal_name == "T2bt_and_T2bw") sp = "T2bt_mStop500_mLSP300";
		if(signal_name == "T2fbd_and_T2bwC") sp = "T2fbd_mStop500_mLSP490";
		if(signal_name == "T2cc_and_T2tt") sp = "T2cc_mStop500_mLSP490";

		TFile *f1 = new TFile(result_path + sp + ".root");
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
			if(plot_SB_team_A_highdm || plot_SB_team_A_lowdm) h1->GetXaxis()->SetNdivisions(30);
			h1->GetXaxis()->SetTitle(title);
			h1->GetYaxis()->SetTitleSize(0.045);
			h1->GetYaxis()->SetTitleOffset(1.2);
		}
		leg->AddEntry(h1,sp,"l");
	}

	if (false)
	{
		if(signal_name == "T1tttt_and_T5ttcc") sp = "T1tttt_mGluino1500_mLSP100";
		if(signal_name == "T2tt_and_T1tttt_high") sp = "T2tt_mStop1000_mLSP1";
		if(signal_name == "T2tt_only") sp = "T2tt_mStop500_mLSP325";
		if(signal_name == "T2bt_and_T2bw") sp = "T2bt_mStop800_mLSP100";
		if(signal_name == "T2fbd_and_T2bwC") sp = "T2fbd_mStop600_mLSP520";
		if(signal_name == "T2cc_and_T2tt") sp = "T2cc_mStop500_mLSP420";
		Plot_1D_AUX_sg (signal_scale, result_path, sp, var, folder, leg, kGreen, rebin, sig_scale_to_BG);
	}

	if (false)
	{
		if(signal_name == "T1tttt_and_T5ttcc") sp = "T5ttcc_mGluino1000_mLSP800";
		if(signal_name == "T2tt_and_T1tttt_high") sp = "T1tttt_mGluino2000_mLSP1000";
		if(signal_name == "T2tt_only") sp = "T2tt_mStop850_mLSP350";
		if(signal_name == "T2bt_and_T2bw") sp = "T2bw_mStop500_mLSP325";
		if(signal_name == "T2fbd_and_T2bwC") sp = "T2bwC_mStop500_mLSP490";
		if(signal_name == "T2cc_and_T2tt") sp = "T2tt_mStop250_mLSP150";
		Plot_1D_AUX_sg (signal_scale, result_path, sp, var, folder, leg, kYellow, rebin, sig_scale_to_BG);
	}

	if (false)
	{
		if(signal_name == "T1tttt_and_T5ttcc") sp = "T5ttcc_mGluino1500_mLSP100";
		if(signal_name == "T2tt_and_T1tttt_high") sp = "T1tttt_mGluino2000_mLSP100";
		if(signal_name == "T2tt_only") sp = "T2tt_mStop850_mLSP100";
		if(signal_name == "T2bt_and_T2bw") sp = "T2bw_mStop800_mLSP100";
		if(signal_name == "T2fbd_and_T2bwC") sp = "T2bwC_mStop600_mLSP520";
		if(signal_name == "T2cc_and_T2tt") sp = "T2tt_mStop425_mLSP325";
		Plot_1D_AUX_sg (signal_scale, result_path, sp, var, folder, leg, kBlue, rebin, sig_scale_to_BG);
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
		if(sig_scale_to_BG) latex.DrawLatex(0.12,0.82,"#bf{signals scaled to BG sum}");
		//if(sig_scale_to_BG) latex.DrawLatex(0.12,0.82,sig_scale);
		else latex.DrawLatex(0.12,0.85,"#bf{signals scaled up X50}");
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
			if(signal_name == "T2tt_test") sp = "T2tt_mStop850_mLSP100_fullsim" + year;
			if(signal_name == "T1tttt_and_T5ttcc") sp = "T1tttt_mGluino1200_mLSP800";
			if(signal_name == "T2tt_and_T1tttt_high") sp = "T2tt_mStop1000_mLSP500";
			if(signal_name == "T2tt_only") sp = "T2tt_mStop425_mLSP325";
			if(signal_name == "T2bt_and_T2bw") sp = "T2bt_mStop500_mLSP300";
			if(signal_name == "T2fbd_and_T2bwC") sp = "T2fbd_mStop500_mLSP490";
			if(signal_name == "T2cc_and_T2tt") sp = "T2cc_mStop500_mLSP490";

			TFile *f1 = new TFile(result_path + sp + ".root");
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
			//h1->Scale(lumi * CrossSection.at(sp) * 1000 / all_events );
			h1->Scale(lumi * 1000);

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
			if(plot_SB_team_A_highdm || plot_SB_team_A_lowdm) significance->GetXaxis()->SetNdivisions(30);
			//significance->GetXaxis()->SetTitle("MT2 [GeV]");
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
			if(signal_name == "T1tttt_and_T5ttcc") sp = "T1tttt_mGluino1500_mLSP100";
			if(signal_name == "T2tt_and_T1tttt_high") sp = "T2tt_mStop1000_mLSP1";
			if(signal_name == "T2tt_only") sp = "T2tt_mStop500_mLSP325";
			if(signal_name == "T2bt_and_T2bw") sp = "T2bt_mStop800_mLSP100";
			if(signal_name == "T2fbd_and_T2bwC") sp = "T2fbd_mStop600_mLSP520";
			if(signal_name == "T2cc_and_T2tt") sp = "T2cc_mStop500_mLSP420";
			Plot_1D_AUX_sig (lumi, result_path, sp, var, folder, leg, kGreen, hs, rebin, use_low_stat_sig);
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
			Plot_1D_AUX_sig (lumi, result_path, sp, var, folder, leg, kYellow, hs, rebin, use_low_stat_sig);
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
			Plot_1D_AUX_sig (lumi, result_path, sp, var, folder, leg, kBlue, hs, rebin, use_low_stat_sig);
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
