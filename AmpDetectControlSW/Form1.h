#pragma once

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <msclr\marshal.h>

#include "AmpDetectDLL.h"
#include "PcrProtocol.h"
HINSTANCE cameraDll;

using namespace System::IO::Ports;
using namespace msclr::interop;
using namespace System::Windows::Forms::DataVisualization::Charting;

typedef struct {
	uint8_t _nCameraIndex;
	uint8_t _nCameraCaptureStart;
	uint8_t _nCameraCaptureDone;
}CameraStatus;

typedef struct {
	HANDLE hFileMap;
	CameraStatus *camCaptureStatus;
	char MapName[256];
	size_t size;
}CameraStatusHeader;

CameraStatusHeader camStatusHdr;
CameraStatus camStatus;

//bool GrabSucceddedStatus(void);
typedef bool (WINAPI* GrabSucceededStatus)(void);
//void CameraCapture(int cameraID, int exposure);
typedef void (WINAPI* CameraCapture)(int cameraID, int exposure, int ledIntensity);
// int GetCameraCaptureError(void);
typedef int (WINAPI* GetCameraCaptureError)(void);
GrabSucceededStatus imageCaptureStatus;
CameraCapture captureImage;
GetCameraCaptureError cameraError;
bool dllFuncValid = false;

namespace CppCLR_WinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	enum StatusGridColIdx
	{
		kSiteNumIdx,
		kStateIdx,
		kSelectedProtocolIdx,
		kSelProtocolBtnIdx,
		kSegmentIdx,
		kCycleIdx,
		kStepIdx,
		kTimeIdx,
		kTemperatureIdx
	};

	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			InitializeCamera();

			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
			OpticsTypeCombo->SelectedIndex = 0;
			Series^ blockSeries = ((System::Collections::Generic::IList<Series^>^)ThermalGraph->Series)[0];
			blockSeries->Points->AddXY(0, 0);
			Series^ illuminatedSeries = ((System::Collections::Generic::IList<Series^>^)OpticalGraph->Series)[0];
			illuminatedSeries->Points->AddXY(0, 45000);

			for (int i = 0; i < 40; i++)
			{
				_arOpticalDataFiles.Add(nullptr);
				_arThermalDataFiles.Add(nullptr);
			}
			this->Text = this->Text + " (" + Application::ProductVersion + ")";
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TabControl^  AmpDetectTabs;
	private: System::Windows::Forms::TabPage^  GraphsTab;

	private: System::Windows::Forms::TabPage^  ProtocolsTab;
	private: System::UInt32				_nHostDevCommErrCode = ErrCode::kNoError;
	private: System::Collections::Generic::List<System::IO::StreamWriter^>	_arOpticalDataFiles;
	private: System::Collections::Generic::List<System::IO::StreamWriter^>	_arThermalDataFiles;
	protected:

	protected:

	protected:


	private: System::Windows::Forms::Button^  SaveProtocol;
	private: System::Windows::Forms::DataGridView^  ProtocolDataGrid;
	private: System::Windows::Forms::RichTextBox^  ProtocolName;
			 //	private: DeviceCommDriver ^ _devCommDrv;


















	private: System::Windows::Forms::Button^  OpenProtocol;
	private: System::Windows::Forms::Button^  NewStep;
	private: System::Windows::Forms::OpenFileDialog^  openProtocolDlg;


























	private: System::Windows::Forms::Button^  DeleteStep;
	private: System::Windows::Forms::SaveFileDialog^  saveProtocolDlg;




	private: System::Windows::Forms::Button^  StopPcrBtn;
	private: System::Windows::Forms::Button^  RunPcrBtn;
	private: System::Windows::Forms::TabPage^  AdvancedTab;



	private: System::Windows::Forms::DataGridView^  RunStatusGrid;





	private: System::Windows::Forms::Timer^  StatusTimer;







	private: System::Windows::Forms::ComboBox^  CommPortSelection;
	private: System::Windows::Forms::Label^  label2;









	private: System::Windows::Forms::DataVisualization::Charting::Chart^  ThermalGraph;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  OpticalGraph;

	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Button^  SelectDataFolderButton;
	private: System::Windows::Forms::RichTextBox^  SelectedDataFolder;

	private: System::Windows::Forms::FolderBrowserDialog^  SelectDataFolderDlg;
private: System::Windows::Forms::Button^  ActuateTemperature;


	private: System::Windows::Forms::Label^  label5;
private: System::Windows::Forms::TextBox^  TemperatureSetpoint;































	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Button^  DelOptReadBtn;

	private: System::Windows::Forms::Button^  AddOptReadBtn;

	private: System::Windows::Forms::DataGridView^  OpticalReadsGrid;





	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::ComboBox^  OpticsTypeCombo;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Cycles;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Steps;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Setpoint;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Time;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  RampRate;
	private: System::Windows::Forms::DataGridViewCheckBoxColumn^  OpticalAcq;
	private: System::Windows::Forms::DataGridViewCheckBoxColumn^  Melt;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  LEDIndex;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  LedIntensity;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  LedStabilizationTime;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  DetectorIndex;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  RefDetectorIndex;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  DetectorIntegrationTime;
	private: System::Windows::Forms::DataGridView^  PidGrid;





	private: System::Windows::Forms::Button^  SetPidParams;






private: System::Windows::Forms::GroupBox^  groupBox3;
private: System::Windows::Forms::Label^  label8;
private: System::Windows::Forms::TextBox^  CurrentSetpoint;
private: System::Windows::Forms::Button^  ActuateCurrent;
private: System::Windows::Forms::Button^  DisableManControlBtn;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  TypeCol;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  PGainCol;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  GainICol;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  GainDCol;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  SlopeCol;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  YInterceptCol;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  StabilizationTolerance;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  StabilizationTime;









private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::NumericUpDown^  DeviceCount;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  SiteCol;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  ActiveCol;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  PcrProtocolCol;
private: System::Windows::Forms::DataGridViewButtonColumn^  SelectPcrProtocol;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  SegmentCol;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  CycleCol;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  StepCol;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  StepTimeCol;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  TemperatureCol;






















































	private: System::ComponentModel::IContainer^  components;
















	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::CustomLabel^  customLabel1 = (gcnew System::Windows::Forms::DataVisualization::Charting::CustomLabel());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series5 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series6 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series7 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series8 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series9 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->AmpDetectTabs = (gcnew System::Windows::Forms::TabControl());
			this->GraphsTab = (gcnew System::Windows::Forms::TabPage());
			this->ThermalGraph = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->OpticalGraph = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->ProtocolsTab = (gcnew System::Windows::Forms::TabPage());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->DelOptReadBtn = (gcnew System::Windows::Forms::Button());
			this->AddOptReadBtn = (gcnew System::Windows::Forms::Button());
			this->OpticalReadsGrid = (gcnew System::Windows::Forms::DataGridView());
			this->LEDIndex = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->LedIntensity = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->LedStabilizationTime = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->DetectorIndex = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->RefDetectorIndex = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->DetectorIntegrationTime = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->OpticsTypeCombo = (gcnew System::Windows::Forms::ComboBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->DeleteStep = (gcnew System::Windows::Forms::Button());
			this->NewStep = (gcnew System::Windows::Forms::Button());
			this->OpenProtocol = (gcnew System::Windows::Forms::Button());
			this->ProtocolName = (gcnew System::Windows::Forms::RichTextBox());
			this->SaveProtocol = (gcnew System::Windows::Forms::Button());
			this->ProtocolDataGrid = (gcnew System::Windows::Forms::DataGridView());
			this->Cycles = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Steps = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Setpoint = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Time = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->RampRate = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->OpticalAcq = (gcnew System::Windows::Forms::DataGridViewCheckBoxColumn());
			this->Melt = (gcnew System::Windows::Forms::DataGridViewCheckBoxColumn());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->AdvancedTab = (gcnew System::Windows::Forms::TabPage());
			this->SetPidParams = (gcnew System::Windows::Forms::Button());
			this->PidGrid = (gcnew System::Windows::Forms::DataGridView());
			this->TypeCol = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->PGainCol = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->GainICol = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->GainDCol = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->SlopeCol = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->YInterceptCol = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->StabilizationTolerance = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->StabilizationTime = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->DisableManControlBtn = (gcnew System::Windows::Forms::Button());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->CurrentSetpoint = (gcnew System::Windows::Forms::TextBox());
			this->ActuateCurrent = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->TemperatureSetpoint = (gcnew System::Windows::Forms::TextBox());
			this->ActuateTemperature = (gcnew System::Windows::Forms::Button());
			this->SelectDataFolderButton = (gcnew System::Windows::Forms::Button());
			this->SelectedDataFolder = (gcnew System::Windows::Forms::RichTextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->CommPortSelection = (gcnew System::Windows::Forms::ComboBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->RunStatusGrid = (gcnew System::Windows::Forms::DataGridView());
			this->SiteCol = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ActiveCol = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->PcrProtocolCol = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->SelectPcrProtocol = (gcnew System::Windows::Forms::DataGridViewButtonColumn());
			this->SegmentCol = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->CycleCol = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->StepCol = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->StepTimeCol = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->TemperatureCol = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->StopPcrBtn = (gcnew System::Windows::Forms::Button());
			this->RunPcrBtn = (gcnew System::Windows::Forms::Button());
			this->openProtocolDlg = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveProtocolDlg = (gcnew System::Windows::Forms::SaveFileDialog());
			this->StatusTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->SelectDataFolderDlg = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->DeviceCount = (gcnew System::Windows::Forms::NumericUpDown());
			this->AmpDetectTabs->SuspendLayout();
			this->GraphsTab->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ThermalGraph))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->OpticalGraph))->BeginInit();
			this->ProtocolsTab->SuspendLayout();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->OpticalReadsGrid))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ProtocolDataGrid))->BeginInit();
			this->AdvancedTab->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PidGrid))->BeginInit();
			this->groupBox3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RunStatusGrid))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DeviceCount))->BeginInit();
			this->SuspendLayout();
			// 
			// AmpDetectTabs
			// 
			this->AmpDetectTabs->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->AmpDetectTabs->Controls->Add(this->GraphsTab);
			this->AmpDetectTabs->Controls->Add(this->ProtocolsTab);
			this->AmpDetectTabs->Controls->Add(this->AdvancedTab);
			this->AmpDetectTabs->Location = System::Drawing::Point(9, 290);
			this->AmpDetectTabs->Margin = System::Windows::Forms::Padding(2);
			this->AmpDetectTabs->Name = L"AmpDetectTabs";
			this->AmpDetectTabs->SelectedIndex = 0;
			this->AmpDetectTabs->Size = System::Drawing::Size(886, 348);
			this->AmpDetectTabs->TabIndex = 0;
			// 
			// GraphsTab
			// 
			this->GraphsTab->Controls->Add(this->ThermalGraph);
			this->GraphsTab->Controls->Add(this->OpticalGraph);
			this->GraphsTab->Location = System::Drawing::Point(4, 22);
			this->GraphsTab->Margin = System::Windows::Forms::Padding(2);
			this->GraphsTab->Name = L"GraphsTab";
			this->GraphsTab->Padding = System::Windows::Forms::Padding(2);
			this->GraphsTab->Size = System::Drawing::Size(878, 322);
			this->GraphsTab->TabIndex = 0;
			this->GraphsTab->Text = L"Graphs (no selection)";
			this->GraphsTab->UseVisualStyleBackColor = true;
			this->GraphsTab->Enter += gcnew System::EventHandler(this, &Form1::AmpDetectTab_Enter);
			// 
			// ThermalGraph
			// 
			this->ThermalGraph->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->ThermalGraph->BorderlineColor = System::Drawing::Color::Black;
			customLabel1->Text = L"*C";
			chartArea1->AxisX->CustomLabels->Add(customLabel1);
			chartArea1->AxisY->Maximum = 100;
			chartArea1->AxisY->Minimum = 50;
			chartArea1->AxisY2->Maximum = 20;
			chartArea1->AxisY2->Minimum = -20;
			chartArea1->Name = L"ChartArea1";
			this->ThermalGraph->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->ThermalGraph->Legends->Add(legend1);
			this->ThermalGraph->Location = System::Drawing::Point(7, 178);
			this->ThermalGraph->Margin = System::Windows::Forms::Padding(2);
			this->ThermalGraph->Name = L"ThermalGraph";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series1->Legend = L"Legend1";
			series1->Name = L"Block";
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series2->Legend = L"Legend1";
			series2->Name = L"Top Heater";
			series3->ChartArea = L"ChartArea1";
			series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series3->Legend = L"Legend1";
			series3->Name = L"Current";
			series4->ChartArea = L"ChartArea1";
			series4->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series4->Legend = L"Legend1";
			series4->Name = L"Sample";
			this->ThermalGraph->Series->Add(series1);
			this->ThermalGraph->Series->Add(series2);
			this->ThermalGraph->Series->Add(series3);
			this->ThermalGraph->Series->Add(series4);
			this->ThermalGraph->Size = System::Drawing::Size(857, 140);
			this->ThermalGraph->TabIndex = 11;
			this->ThermalGraph->Text = L"Thermal Data";
			// 
			// OpticalGraph
			// 
			this->OpticalGraph->Anchor = System::Windows::Forms::AnchorStyles::None;
			chartArea2->Name = L"ChartArea1";
			this->OpticalGraph->ChartAreas->Add(chartArea2);
			legend2->Name = L"Legend1";
			this->OpticalGraph->Legends->Add(legend2);
			this->OpticalGraph->Location = System::Drawing::Point(7, 29);
			this->OpticalGraph->Margin = System::Windows::Forms::Padding(2);
			this->OpticalGraph->Name = L"OpticalGraph";
			series5->ChartArea = L"ChartArea1";
			series5->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series5->Legend = L"Legend1";
			series5->Name = L"Illuminated";
			series6->ChartArea = L"ChartArea1";
			series6->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series6->Legend = L"Legend1";
			series6->Name = L"Dark";
			series7->ChartArea = L"ChartArea1";
			series7->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series7->Legend = L"Legend1";
			series7->Name = L"Temperature";
			series8->ChartArea = L"ChartArea1";
			series8->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series8->Legend = L"Legend1";
			series8->Name = L"RefIlluminated";
			series9->ChartArea = L"ChartArea1";
			series9->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series9->Legend = L"Legend1";
			series9->Name = L"RefDark";
			this->OpticalGraph->Series->Add(series5);
			this->OpticalGraph->Series->Add(series6);
			this->OpticalGraph->Series->Add(series7);
			this->OpticalGraph->Series->Add(series8);
			this->OpticalGraph->Series->Add(series9);
			this->OpticalGraph->Size = System::Drawing::Size(857, 134);
			this->OpticalGraph->TabIndex = 10;
			this->OpticalGraph->Text = L"Optical Data";
			// 
			// ProtocolsTab
			// 
			this->ProtocolsTab->Controls->Add(this->groupBox1);
			this->ProtocolsTab->Controls->Add(this->DeleteStep);
			this->ProtocolsTab->Controls->Add(this->NewStep);
			this->ProtocolsTab->Controls->Add(this->OpenProtocol);
			this->ProtocolsTab->Controls->Add(this->ProtocolName);
			this->ProtocolsTab->Controls->Add(this->SaveProtocol);
			this->ProtocolsTab->Controls->Add(this->ProtocolDataGrid);
			this->ProtocolsTab->Controls->Add(this->groupBox2);
			this->ProtocolsTab->Location = System::Drawing::Point(4, 22);
			this->ProtocolsTab->Margin = System::Windows::Forms::Padding(2);
			this->ProtocolsTab->Name = L"ProtocolsTab";
			this->ProtocolsTab->Padding = System::Windows::Forms::Padding(2);
			this->ProtocolsTab->Size = System::Drawing::Size(878, 322);
			this->ProtocolsTab->TabIndex = 1;
			this->ProtocolsTab->Text = L"Protocols";
			this->ProtocolsTab->UseVisualStyleBackColor = true;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->DelOptReadBtn);
			this->groupBox1->Controls->Add(this->AddOptReadBtn);
			this->groupBox1->Controls->Add(this->OpticalReadsGrid);
			this->groupBox1->Controls->Add(this->label7);
			this->groupBox1->Controls->Add(this->OpticsTypeCombo);
			this->groupBox1->Controls->Add(this->label6);
			this->groupBox1->Location = System::Drawing::Point(5, 362);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(868, 213);
			this->groupBox1->TabIndex = 10;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Optics";
			// 
			// DelOptReadBtn
			// 
			this->DelOptReadBtn->Location = System::Drawing::Point(38, 123);
			this->DelOptReadBtn->Margin = System::Windows::Forms::Padding(2);
			this->DelOptReadBtn->Name = L"DelOptReadBtn";
			this->DelOptReadBtn->Size = System::Drawing::Size(120, 23);
			this->DelOptReadBtn->TabIndex = 11;
			this->DelOptReadBtn->Text = L"Delete";
			this->DelOptReadBtn->UseVisualStyleBackColor = true;
			this->DelOptReadBtn->Click += gcnew System::EventHandler(this, &Form1::DelOptReadBtn_Click);
			// 
			// AddOptReadBtn
			// 
			this->AddOptReadBtn->Location = System::Drawing::Point(38, 84);
			this->AddOptReadBtn->Margin = System::Windows::Forms::Padding(2);
			this->AddOptReadBtn->Name = L"AddOptReadBtn";
			this->AddOptReadBtn->Size = System::Drawing::Size(120, 23);
			this->AddOptReadBtn->TabIndex = 10;
			this->AddOptReadBtn->Text = L"Add";
			this->AddOptReadBtn->UseVisualStyleBackColor = true;
			this->AddOptReadBtn->Click += gcnew System::EventHandler(this, &Form1::AddOptReadBtn_Click);
			// 
			// OpticalReadsGrid
			// 
			this->OpticalReadsGrid->AllowUserToAddRows = false;
			this->OpticalReadsGrid->AllowUserToDeleteRows = false;
			this->OpticalReadsGrid->AllowUserToResizeColumns = false;
			this->OpticalReadsGrid->AllowUserToResizeRows = false;
			this->OpticalReadsGrid->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->OpticalReadsGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->OpticalReadsGrid->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(6) {
				this->LEDIndex,
					this->LedIntensity, this->LedStabilizationTime, this->DetectorIndex, this->RefDetectorIndex, this->DetectorIntegrationTime
			});
			this->OpticalReadsGrid->Location = System::Drawing::Point(175, 44);
			this->OpticalReadsGrid->Margin = System::Windows::Forms::Padding(2);
			this->OpticalReadsGrid->Name = L"OpticalReadsGrid";
			this->OpticalReadsGrid->RowTemplate->Height = 24;
			this->OpticalReadsGrid->Size = System::Drawing::Size(577, 151);
			this->OpticalReadsGrid->TabIndex = 3;
			// 
			// LEDIndex
			// 
			this->LEDIndex->HeaderText = L"LED Index";
			this->LEDIndex->Name = L"LEDIndex";
			this->LEDIndex->Width = 75;
			// 
			// LedIntensity
			// 
			this->LedIntensity->HeaderText = L"LED Intensity";
			this->LedIntensity->Name = L"LedIntensity";
			// 
			// LedStabilizationTime
			// 
			this->LedStabilizationTime->HeaderText = L"LED Stabilization Time (us)";
			this->LedStabilizationTime->Name = L"LedStabilizationTime";
			// 
			// DetectorIndex
			// 
			this->DetectorIndex->HeaderText = L"Detector Index";
			this->DetectorIndex->Name = L"DetectorIndex";
			this->DetectorIndex->Width = 75;
			// 
			// RefDetectorIndex
			// 
			this->RefDetectorIndex->HeaderText = L"RefDetector Index";
			this->RefDetectorIndex->Name = L"RefDetectorIndex";
			this->RefDetectorIndex->Width = 75;
			// 
			// DetectorIntegrationTime
			// 
			this->DetectorIntegrationTime->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->DetectorIntegrationTime->HeaderText = L"Detector Integration Time (us)";
			this->DetectorIntegrationTime->Name = L"DetectorIntegrationTime";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(172, 28);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(72, 13);
			this->label7->TabIndex = 2;
			this->label7->Text = L"Optical reads:";
			// 
			// OpticsTypeCombo
			// 
			this->OpticsTypeCombo->FormattingEnabled = true;
			this->OpticsTypeCombo->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Photodiode", L"Camera" });
			this->OpticsTypeCombo->Location = System::Drawing::Point(9, 44);
			this->OpticsTypeCombo->Name = L"OpticsTypeCombo";
			this->OpticsTypeCombo->Size = System::Drawing::Size(149, 21);
			this->OpticsTypeCombo->TabIndex = 1;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(6, 28);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(34, 13);
			this->label6->TabIndex = 0;
			this->label6->Text = L"Type:";
			// 
			// DeleteStep
			// 
			this->DeleteStep->Location = System::Drawing::Point(43, 156);
			this->DeleteStep->Margin = System::Windows::Forms::Padding(2);
			this->DeleteStep->Name = L"DeleteStep";
			this->DeleteStep->Size = System::Drawing::Size(120, 23);
			this->DeleteStep->TabIndex = 7;
			this->DeleteStep->Text = L"Delete Step";
			this->DeleteStep->UseVisualStyleBackColor = true;
			this->DeleteStep->Click += gcnew System::EventHandler(this, &Form1::DeleteStep_Click);
			// 
			// NewStep
			// 
			this->NewStep->Location = System::Drawing::Point(43, 118);
			this->NewStep->Margin = System::Windows::Forms::Padding(2);
			this->NewStep->Name = L"NewStep";
			this->NewStep->Size = System::Drawing::Size(120, 23);
			this->NewStep->TabIndex = 6;
			this->NewStep->Text = L"New Step";
			this->NewStep->UseVisualStyleBackColor = true;
			this->NewStep->Click += gcnew System::EventHandler(this, &Form1::NewStep_Click);
			// 
			// OpenProtocol
			// 
			this->OpenProtocol->Location = System::Drawing::Point(339, 17);
			this->OpenProtocol->Margin = System::Windows::Forms::Padding(2);
			this->OpenProtocol->Name = L"OpenProtocol";
			this->OpenProtocol->Size = System::Drawing::Size(52, 20);
			this->OpenProtocol->TabIndex = 4;
			this->OpenProtocol->Text = L"...";
			this->OpenProtocol->UseVisualStyleBackColor = true;
			this->OpenProtocol->Click += gcnew System::EventHandler(this, &Form1::OpenProtocol_Click);
			// 
			// ProtocolName
			// 
			this->ProtocolName->Location = System::Drawing::Point(14, 13);
			this->ProtocolName->Margin = System::Windows::Forms::Padding(2);
			this->ProtocolName->Name = L"ProtocolName";
			this->ProtocolName->ReadOnly = true;
			this->ProtocolName->Size = System::Drawing::Size(312, 24);
			this->ProtocolName->TabIndex = 3;
			this->ProtocolName->Text = L"";
			// 
			// SaveProtocol
			// 
			this->SaveProtocol->Location = System::Drawing::Point(753, 11);
			this->SaveProtocol->Margin = System::Windows::Forms::Padding(2);
			this->SaveProtocol->Name = L"SaveProtocol";
			this->SaveProtocol->Size = System::Drawing::Size(120, 23);
			this->SaveProtocol->TabIndex = 2;
			this->SaveProtocol->Text = L"Save Protocol";
			this->SaveProtocol->UseVisualStyleBackColor = true;
			this->SaveProtocol->Click += gcnew System::EventHandler(this, &Form1::SaveProtocol_Click);
			// 
			// ProtocolDataGrid
			// 
			this->ProtocolDataGrid->AllowUserToAddRows = false;
			this->ProtocolDataGrid->AllowUserToDeleteRows = false;
			this->ProtocolDataGrid->AllowUserToResizeColumns = false;
			this->ProtocolDataGrid->AllowUserToResizeRows = false;
			this->ProtocolDataGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->ProtocolDataGrid->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(7) {
				this->Cycles,
					this->Steps, this->Setpoint, this->Time, this->RampRate, this->OpticalAcq, this->Melt
			});
			this->ProtocolDataGrid->Location = System::Drawing::Point(180, 118);
			this->ProtocolDataGrid->Margin = System::Windows::Forms::Padding(2);
			this->ProtocolDataGrid->Name = L"ProtocolDataGrid";
			this->ProtocolDataGrid->RowTemplate->Height = 24;
			this->ProtocolDataGrid->Size = System::Drawing::Size(577, 196);
			this->ProtocolDataGrid->TabIndex = 0;
			// 
			// Cycles
			// 
			this->Cycles->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::ColumnHeader;
			this->Cycles->HeaderText = L"Cycles";
			this->Cycles->Name = L"Cycles";
			this->Cycles->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->Cycles->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Cycles->Width = 44;
			// 
			// Steps
			// 
			this->Steps->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::ColumnHeader;
			this->Steps->HeaderText = L"Step";
			this->Steps->Name = L"Steps";
			this->Steps->ReadOnly = true;
			this->Steps->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->Steps->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Steps->Width = 35;
			// 
			// Setpoint
			// 
			this->Setpoint->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::ColumnHeader;
			this->Setpoint->HeaderText = L"Setpoint (C)";
			this->Setpoint->Name = L"Setpoint";
			this->Setpoint->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->Setpoint->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Setpoint->Width = 68;
			// 
			// Time
			// 
			this->Time->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::ColumnHeader;
			this->Time->HeaderText = L"Time (s)";
			this->Time->Name = L"Time";
			this->Time->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->Time->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Time->Width = 50;
			// 
			// RampRate
			// 
			this->RampRate->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::ColumnHeader;
			this->RampRate->HeaderText = L"Ramp (C/s)";
			this->RampRate->Name = L"RampRate";
			this->RampRate->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->RampRate->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->RampRate->Width = 67;
			// 
			// OpticalAcq
			// 
			this->OpticalAcq->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::ColumnHeader;
			this->OpticalAcq->HeaderText = L"Optical Read";
			this->OpticalAcq->Name = L"OpticalAcq";
			this->OpticalAcq->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->OpticalAcq->Width = 75;
			// 
			// Melt
			// 
			this->Melt->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->Melt->HeaderText = L"Melt";
			this->Melt->Name = L"Melt";
			this->Melt->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			// 
			// groupBox2
			// 
			this->groupBox2->Location = System::Drawing::Point(5, 81);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(868, 256);
			this->groupBox2->TabIndex = 9;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Thermal Profile";
			// 
			// AdvancedTab
			// 
			this->AdvancedTab->Controls->Add(this->SetPidParams);
			this->AdvancedTab->Controls->Add(this->PidGrid);
			this->AdvancedTab->Controls->Add(this->groupBox3);
			this->AdvancedTab->Location = System::Drawing::Point(4, 22);
			this->AdvancedTab->Margin = System::Windows::Forms::Padding(2);
			this->AdvancedTab->Name = L"AdvancedTab";
			this->AdvancedTab->Size = System::Drawing::Size(878, 322);
			this->AdvancedTab->TabIndex = 2;
			this->AdvancedTab->Text = L"Advanced (no selection)";
			this->AdvancedTab->UseVisualStyleBackColor = true;
			this->AdvancedTab->TextChanged += gcnew System::EventHandler(this, &Form1::AdvancedTab_TextChanged);
			this->AdvancedTab->Enter += gcnew System::EventHandler(this, &Form1::AdvancedTab_Enter);
			// 
			// SetPidParams
			// 
			this->SetPidParams->Location = System::Drawing::Point(818, 113);
			this->SetPidParams->Margin = System::Windows::Forms::Padding(2);
			this->SetPidParams->Name = L"SetPidParams";
			this->SetPidParams->Size = System::Drawing::Size(56, 19);
			this->SetPidParams->TabIndex = 4;
			this->SetPidParams->Text = L"Set";
			this->SetPidParams->UseVisualStyleBackColor = true;
			this->SetPidParams->Click += gcnew System::EventHandler(this, &Form1::SetPidParams_Click);
			// 
			// PidGrid
			// 
			this->PidGrid->AllowUserToAddRows = false;
			this->PidGrid->AllowUserToDeleteRows = false;
			this->PidGrid->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::ColumnHeader;
			this->PidGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->PidGrid->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(8) {
				this->TypeCol, this->PGainCol,
					this->GainICol, this->GainDCol, this->SlopeCol, this->YInterceptCol, this->StabilizationTolerance, this->StabilizationTime
			});
			this->PidGrid->Location = System::Drawing::Point(3, 113);
			this->PidGrid->Name = L"PidGrid";
			this->PidGrid->Size = System::Drawing::Size(810, 157);
			this->PidGrid->TabIndex = 3;
			// 
			// TypeCol
			// 
			this->TypeCol->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::AllCells;
			this->TypeCol->HeaderText = L"Type";
			this->TypeCol->Name = L"TypeCol";
			this->TypeCol->ReadOnly = true;
			this->TypeCol->Width = 56;
			// 
			// PGainCol
			// 
			this->PGainCol->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::AllCells;
			this->PGainCol->HeaderText = L"Kp";
			this->PGainCol->Name = L"PGainCol";
			this->PGainCol->Width = 45;
			// 
			// GainICol
			// 
			this->GainICol->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::AllCells;
			this->GainICol->HeaderText = L"Ki";
			this->GainICol->Name = L"GainICol";
			this->GainICol->Width = 41;
			// 
			// GainDCol
			// 
			this->GainDCol->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::AllCells;
			this->GainDCol->HeaderText = L"Kd";
			this->GainDCol->Name = L"GainDCol";
			this->GainDCol->Width = 45;
			// 
			// SlopeCol
			// 
			this->SlopeCol->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::AllCells;
			this->SlopeCol->HeaderText = L"Slope";
			this->SlopeCol->Name = L"SlopeCol";
			this->SlopeCol->Width = 59;
			// 
			// YInterceptCol
			// 
			this->YInterceptCol->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::AllCells;
			this->YInterceptCol->HeaderText = L"Y Intercept";
			this->YInterceptCol->Name = L"YInterceptCol";
			this->YInterceptCol->Width = 78;
			// 
			// StabilizationTolerance
			// 
			this->StabilizationTolerance->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::AllCells;
			this->StabilizationTolerance->HeaderText = L"Stabilization Tolerance (*C)";
			this->StabilizationTolerance->Name = L"StabilizationTolerance";
			this->StabilizationTolerance->Width = 130;
			// 
			// StabilizationTime
			// 
			this->StabilizationTime->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::AllCells;
			this->StabilizationTime->HeaderText = L"Stabilization Time (s)";
			this->StabilizationTime->Name = L"StabilizationTime";
			this->StabilizationTime->Width = 107;
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->DisableManControlBtn);
			this->groupBox3->Controls->Add(this->label8);
			this->groupBox3->Controls->Add(this->CurrentSetpoint);
			this->groupBox3->Controls->Add(this->ActuateCurrent);
			this->groupBox3->Controls->Add(this->label5);
			this->groupBox3->Controls->Add(this->TemperatureSetpoint);
			this->groupBox3->Controls->Add(this->ActuateTemperature);
			this->groupBox3->Location = System::Drawing::Point(3, 3);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(876, 86);
			this->groupBox3->TabIndex = 5;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Manual Control";
			// 
			// DisableManControlBtn
			// 
			this->DisableManControlBtn->Location = System::Drawing::Point(696, 18);
			this->DisableManControlBtn->Margin = System::Windows::Forms::Padding(2);
			this->DisableManControlBtn->Name = L"DisableManControlBtn";
			this->DisableManControlBtn->Size = System::Drawing::Size(175, 19);
			this->DisableManControlBtn->TabIndex = 6;
			this->DisableManControlBtn->Text = L"Disable Manual Control";
			this->DisableManControlBtn->UseVisualStyleBackColor = true;
			this->DisableManControlBtn->Click += gcnew System::EventHandler(this, &Form1::DisableManControlBtn_Click);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(5, 57);
			this->label8->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(60, 13);
			this->label8->TabIndex = 4;
			this->label8->Text = L"Current (A):";
			// 
			// CurrentSetpoint
			// 
			this->CurrentSetpoint->Location = System::Drawing::Point(133, 54);
			this->CurrentSetpoint->Margin = System::Windows::Forms::Padding(2);
			this->CurrentSetpoint->Name = L"CurrentSetpoint";
			this->CurrentSetpoint->Size = System::Drawing::Size(56, 20);
			this->CurrentSetpoint->TabIndex = 3;
			// 
			// ActuateCurrent
			// 
			this->ActuateCurrent->Location = System::Drawing::Point(202, 54);
			this->ActuateCurrent->Margin = System::Windows::Forms::Padding(2);
			this->ActuateCurrent->Name = L"ActuateCurrent";
			this->ActuateCurrent->Size = System::Drawing::Size(56, 19);
			this->ActuateCurrent->TabIndex = 5;
			this->ActuateCurrent->Text = L"Actuate";
			this->ActuateCurrent->UseVisualStyleBackColor = true;
			this->ActuateCurrent->Click += gcnew System::EventHandler(this, &Form1::ActuateCurrent_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(5, 33);
			this->label5->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(120, 13);
			this->label5->TabIndex = 1;
			this->label5->Text = L"Block Temperature (*C):";
			// 
			// TemperatureSetpoint
			// 
			this->TemperatureSetpoint->Location = System::Drawing::Point(133, 30);
			this->TemperatureSetpoint->Margin = System::Windows::Forms::Padding(2);
			this->TemperatureSetpoint->Name = L"TemperatureSetpoint";
			this->TemperatureSetpoint->Size = System::Drawing::Size(56, 20);
			this->TemperatureSetpoint->TabIndex = 0;
			// 
			// ActuateTemperature
			// 
			this->ActuateTemperature->Location = System::Drawing::Point(202, 30);
			this->ActuateTemperature->Margin = System::Windows::Forms::Padding(2);
			this->ActuateTemperature->Name = L"ActuateTemperature";
			this->ActuateTemperature->Size = System::Drawing::Size(56, 19);
			this->ActuateTemperature->TabIndex = 2;
			this->ActuateTemperature->Text = L"Actuate";
			this->ActuateTemperature->UseVisualStyleBackColor = true;
			this->ActuateTemperature->Click += gcnew System::EventHandler(this, &Form1::ActuateTemperature_Click);
			// 
			// SelectDataFolderButton
			// 
			this->SelectDataFolderButton->Location = System::Drawing::Point(397, 7);
			this->SelectDataFolderButton->Margin = System::Windows::Forms::Padding(2);
			this->SelectDataFolderButton->Name = L"SelectDataFolderButton";
			this->SelectDataFolderButton->Size = System::Drawing::Size(32, 26);
			this->SelectDataFolderButton->TabIndex = 14;
			this->SelectDataFolderButton->Text = L"...";
			this->SelectDataFolderButton->UseVisualStyleBackColor = true;
			this->SelectDataFolderButton->Click += gcnew System::EventHandler(this, &Form1::SelectDataFolderButton_Click);
			// 
			// SelectedDataFolder
			// 
			this->SelectedDataFolder->Location = System::Drawing::Point(88, 7);
			this->SelectedDataFolder->Margin = System::Windows::Forms::Padding(2);
			this->SelectedDataFolder->Multiline = false;
			this->SelectedDataFolder->Name = L"SelectedDataFolder";
			this->SelectedDataFolder->ReadOnly = true;
			this->SelectedDataFolder->Size = System::Drawing::Size(306, 27);
			this->SelectedDataFolder->TabIndex = 13;
			this->SelectedDataFolder->Text = L"";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(11, 7);
			this->label4->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(65, 13);
			this->label4->TabIndex = 12;
			this->label4->Text = L"Data Folder:";
			// 
			// CommPortSelection
			// 
			this->CommPortSelection->AllowDrop = true;
			this->CommPortSelection->FormattingEnabled = true;
			this->CommPortSelection->Location = System::Drawing::Point(789, 4);
			this->CommPortSelection->Margin = System::Windows::Forms::Padding(2);
			this->CommPortSelection->Name = L"CommPortSelection";
			this->CommPortSelection->Size = System::Drawing::Size(107, 21);
			this->CommPortSelection->TabIndex = 7;
			this->CommPortSelection->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::CommPortSelection_SelectedIndexChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(709, 7);
			this->label2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(75, 13);
			this->label2->TabIndex = 6;
			this->label2->Text = L"1st Device ID:";
			// 
			// RunStatusGrid
			// 
			this->RunStatusGrid->AllowUserToAddRows = false;
			this->RunStatusGrid->AllowUserToDeleteRows = false;
			this->RunStatusGrid->AllowUserToResizeColumns = false;
			this->RunStatusGrid->AllowUserToResizeRows = false;
			this->RunStatusGrid->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->RunStatusGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->RunStatusGrid->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(9) {
				this->SiteCol,
					this->ActiveCol, this->PcrProtocolCol, this->SelectPcrProtocol, this->SegmentCol, this->CycleCol, this->StepCol, this->StepTimeCol,
					this->TemperatureCol
			});
			this->RunStatusGrid->Location = System::Drawing::Point(88, 75);
			this->RunStatusGrid->Margin = System::Windows::Forms::Padding(2);
			this->RunStatusGrid->Name = L"RunStatusGrid";
			this->RunStatusGrid->ReadOnly = true;
			this->RunStatusGrid->RowHeadersVisible = false;
			this->RunStatusGrid->RowTemplate->Height = 24;
			this->RunStatusGrid->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->RunStatusGrid->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->RunStatusGrid->Size = System::Drawing::Size(807, 195);
			this->RunStatusGrid->TabIndex = 5;
			this->RunStatusGrid->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form1::RunStatusGrid_CellContentClick);
			this->RunStatusGrid->SelectionChanged += gcnew System::EventHandler(this, &Form1::RunStatusGrid_SelectionChanged);
			// 
			// SiteCol
			// 
			this->SiteCol->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::AllCells;
			this->SiteCol->HeaderText = L"Site";
			this->SiteCol->Name = L"SiteCol";
			this->SiteCol->ReadOnly = true;
			this->SiteCol->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->SiteCol->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->SiteCol->Width = 31;
			// 
			// ActiveCol
			// 
			this->ActiveCol->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::AllCellsExceptHeader;
			this->ActiveCol->HeaderText = L"";
			this->ActiveCol->MinimumWidth = 60;
			this->ActiveCol->Name = L"ActiveCol";
			this->ActiveCol->ReadOnly = true;
			this->ActiveCol->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->ActiveCol->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->ActiveCol->Width = 60;
			// 
			// PcrProtocolCol
			// 
			this->PcrProtocolCol->HeaderText = L"Protocol";
			this->PcrProtocolCol->Name = L"PcrProtocolCol";
			this->PcrProtocolCol->ReadOnly = true;
			this->PcrProtocolCol->Width = 300;
			// 
			// SelectPcrProtocol
			// 
			this->SelectPcrProtocol->HeaderText = L"";
			this->SelectPcrProtocol->Name = L"SelectPcrProtocol";
			this->SelectPcrProtocol->ReadOnly = true;
			this->SelectPcrProtocol->Width = 25;
			// 
			// SegmentCol
			// 
			this->SegmentCol->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::ColumnHeader;
			this->SegmentCol->HeaderText = L"Segment";
			this->SegmentCol->Name = L"SegmentCol";
			this->SegmentCol->ReadOnly = true;
			this->SegmentCol->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->SegmentCol->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->SegmentCol->Width = 55;
			// 
			// CycleCol
			// 
			this->CycleCol->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::ColumnHeader;
			this->CycleCol->HeaderText = L"Cycle";
			this->CycleCol->Name = L"CycleCol";
			this->CycleCol->ReadOnly = true;
			this->CycleCol->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->CycleCol->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->CycleCol->Width = 39;
			// 
			// StepCol
			// 
			this->StepCol->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::ColumnHeader;
			this->StepCol->HeaderText = L"Step";
			this->StepCol->Name = L"StepCol";
			this->StepCol->ReadOnly = true;
			this->StepCol->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->StepCol->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::Programmatic;
			this->StepCol->Width = 54;
			// 
			// StepTimeCol
			// 
			this->StepTimeCol->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::ColumnHeader;
			this->StepTimeCol->HeaderText = L"Time";
			this->StepTimeCol->Name = L"StepTimeCol";
			this->StepTimeCol->ReadOnly = true;
			this->StepTimeCol->Width = 55;
			// 
			// TemperatureCol
			// 
			this->TemperatureCol->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->TemperatureCol->HeaderText = L"*C";
			this->TemperatureCol->Name = L"TemperatureCol";
			this->TemperatureCol->ReadOnly = true;
			this->TemperatureCol->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// StopPcrBtn
			// 
			this->StopPcrBtn->Location = System::Drawing::Point(9, 157);
			this->StopPcrBtn->Margin = System::Windows::Forms::Padding(2);
			this->StopPcrBtn->Name = L"StopPcrBtn";
			this->StopPcrBtn->Size = System::Drawing::Size(56, 26);
			this->StopPcrBtn->TabIndex = 1;
			this->StopPcrBtn->Text = L"Stop";
			this->StopPcrBtn->UseVisualStyleBackColor = true;
			this->StopPcrBtn->Click += gcnew System::EventHandler(this, &Form1::StopPcrBtn_Click);
			// 
			// RunPcrBtn
			// 
			this->RunPcrBtn->Location = System::Drawing::Point(9, 75);
			this->RunPcrBtn->Margin = System::Windows::Forms::Padding(2);
			this->RunPcrBtn->Name = L"RunPcrBtn";
			this->RunPcrBtn->Size = System::Drawing::Size(56, 26);
			this->RunPcrBtn->TabIndex = 0;
			this->RunPcrBtn->Text = L"Start";
			this->RunPcrBtn->UseVisualStyleBackColor = true;
			this->RunPcrBtn->Click += gcnew System::EventHandler(this, &Form1::StartPcrBtn_Click);
			// 
			// StatusTimer
			// 
			this->StatusTimer->Enabled = true;
			this->StatusTimer->Tick += gcnew System::EventHandler(this, &Form1::StatusTimer_Tick);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(709, 37);
			this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(75, 13);
			this->label1->TabIndex = 15;
			this->label1->Text = L"Device Count:";
			// 
			// DeviceCount
			// 
			this->DeviceCount->Location = System::Drawing::Point(789, 35);
			this->DeviceCount->Name = L"DeviceCount";
			this->DeviceCount->Size = System::Drawing::Size(105, 20);
			this->DeviceCount->TabIndex = 16;
			this->DeviceCount->ValueChanged += gcnew System::EventHandler(this, &Form1::DeviceCount_ValueChanged);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(904, 648);
			this->Controls->Add(this->DeviceCount);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->SelectDataFolderButton);
			this->Controls->Add(this->AmpDetectTabs);
			this->Controls->Add(this->RunPcrBtn);
			this->Controls->Add(this->StopPcrBtn);
			this->Controls->Add(this->SelectedDataFolder);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->CommPortSelection);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->RunStatusGrid);
			this->Name = L"Form1";
			this->Text = L"AmpDetect";
			this->AmpDetectTabs->ResumeLayout(false);
			this->GraphsTab->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ThermalGraph))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->OpticalGraph))->EndInit();
			this->ProtocolsTab->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->OpticalReadsGrid))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ProtocolDataGrid))->EndInit();
			this->AdvancedTab->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PidGrid))->EndInit();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RunStatusGrid))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DeviceCount))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void OpenProtocol_Click(System::Object^  sender, System::EventArgs^  e)
	{
		openProtocolDlg->FileName = ProtocolName->Text;
		openProtocolDlg->AddExtension = true;
		openProtocolDlg->Filter = "pcr protocols (*.qpcr)|*.qpcr|All files (*.*)|*.*";

		if (openProtocolDlg->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			ProtocolName->Text = openProtocolDlg->FileName;
			System::IO::StreamReader^ file = gcnew System::IO::StreamReader(ProtocolName->Text);
			System::IO::BinaryReader^ binFile = gcnew System::IO::BinaryReader(file->BaseStream);

			array<uint8_t>^ protocolBuf = binFile->ReadBytes((int)binFile->BaseStream->Length);
			uint8_t arTemp[5 * 1024];
			for (int i = 0; i < (int)binFile->BaseStream->Length; i++)
				arTemp[i] = protocolBuf[i];

			PcrProtocol pcrProtocol;
			pcrProtocol << arTemp;
			WritePcrProtocolToGui(pcrProtocol);
			binFile->Close();
		}
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void SaveProtocol_Click(System::Object^  sender, System::EventArgs^  e)
	{
		saveProtocolDlg->FileName = ProtocolName->Text;
		saveProtocolDlg->AddExtension = true;
		saveProtocolDlg->OverwritePrompt = true;
		saveProtocolDlg->Filter = "pcr protocols (*.qpcr)|*.qpcr|All files (*.*)|*.*";

		PcrProtocol	pcrProtocol;
		ReadPcrProtocolFromGui(&pcrProtocol);
		if (saveProtocolDlg->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			ProtocolName->Text = saveProtocolDlg->FileName;
			System::IO::StreamWriter^ file = gcnew System::IO::StreamWriter(ProtocolName->Text);
			System::IO::BinaryWriter^ binFile = gcnew System::IO::BinaryWriter(file->BaseStream);

			uint8_t arTemp[5 * 1024];
			pcrProtocol >> arTemp;
			array<uint8_t>^ protocolBuf = gcnew array<uint8_t>(pcrProtocol.GetStreamSize());
			for (int i = 0; i < (int)pcrProtocol.GetStreamSize(); i++)
				protocolBuf[i] = arTemp[i];

			binFile->BaseStream->SetLength(0);
			binFile->Write(protocolBuf);
			binFile->Close();
		}
		WritePcrProtocolToGui(pcrProtocol);
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void WritePcrProtocolToGui(PcrProtocol& pcrProtocol)
	{
		ProtocolDataGrid->Rows->Clear();
		OpticalReadsGrid->Rows->Clear();

		//Iterate through all optical reads in this protocol.
		OpticsTypeCombo->SelectedIndex = pcrProtocol.GetFluorDetectorType();
		for (int i = 0; i < (int)pcrProtocol.GetNumOpticalReads(); i++)
		{
			DataGridViewRow^ row = gcnew DataGridViewRow;
			OpticalReadsGrid->Rows->Add(row);
			int nRowIdx = OpticalReadsGrid->RowCount - 1;
			OpticalRead optRead = pcrProtocol.GetOpticalRead(i);

			OpticalReadsGrid[0, nRowIdx]->Value = optRead.GetLedIdx();
			OpticalReadsGrid[1, nRowIdx]->Value = optRead.GetLedIntensity();
			OpticalReadsGrid[2, nRowIdx]->Value = optRead.GetLedStablizationTime();
			OpticalReadsGrid[3, nRowIdx]->Value = optRead.GetDetectorIdx();
			OpticalReadsGrid[4, nRowIdx]->Value = optRead.GetReferenceIdx();
			OpticalReadsGrid[5, nRowIdx]->Value = optRead.GetDetectorIntegrationTime();
		}

		//Iterate through all segments in this protocol.
		for (int nSegIdx = 0; nSegIdx < (int)pcrProtocol.GetNumSegs(); nSegIdx++)
		{
			Segment seg = pcrProtocol.GetSegment(nSegIdx);

			//Iterate through all steps in this segment.
			for (int nStepIdx = 0; nStepIdx < (int)seg.GetNumSteps(); nStepIdx++)
			{
				DataGridViewRow^ row = gcnew DataGridViewRow;
				ProtocolDataGrid->Rows->Add(row);
				int nRowIdx = ProtocolDataGrid->RowCount - 1;
				Step step = seg.GetStep(nStepIdx);

				//If this is the first step in the segment, report number of cycles.
				if (nStepIdx == 0)
					ProtocolDataGrid[0, nRowIdx]->Value = Convert::ToString(seg.GetNumCycles());

				ProtocolDataGrid[1, nRowIdx]->Value = Convert::ToString(nStepIdx + 1);
				ProtocolDataGrid[2, nRowIdx]->Value = Convert::ToString((double)step.GetTargetTemp() / 1000);
				ProtocolDataGrid[3, nRowIdx]->Value = Convert::ToString((double)step.GetHoldTimer() / 1000);
				ProtocolDataGrid[4, nRowIdx]->Value = Convert::ToString((double)step.GetRampRate() / 1000);

				//Optical acquisition.
				ProtocolDataGrid[5, nRowIdx]->Value = step.GetOpticalAcqFlg();

				//Melt
				ProtocolDataGrid[6, nRowIdx]->Value = step.GetMeltFlg();
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void ReadPcrProtocolFromGui(PcrProtocol* pPcrProtocol)
	{
		pPcrProtocol->Clear();

		OpticalRead optRead;
		pPcrProtocol->SetFluorDetectorType((FluorDetectorType)OpticsTypeCombo->SelectedIndex);
		for (int nRowIdx = 0; nRowIdx < OpticalReadsGrid->Rows->Count; nRowIdx++)
		{
			optRead.SetLedIdx(Convert::ToInt32(OpticalReadsGrid[0, nRowIdx]->Value));
			optRead.SetLedIntensity(Convert::ToInt32(OpticalReadsGrid[1, nRowIdx]->Value));
			optRead.SetLedStablizationTime(Convert::ToInt32(OpticalReadsGrid[2, nRowIdx]->Value));
			optRead.SetDetectorIdx(Convert::ToInt32(OpticalReadsGrid[3, nRowIdx]->Value));
			optRead.SetReferenceIdx(Convert::ToInt32(OpticalReadsGrid[4, nRowIdx]->Value));
			optRead.SetDetectorIntegrationTime(Convert::ToInt32(OpticalReadsGrid[5, nRowIdx]->Value));
			pPcrProtocol->AddOpticalRead(optRead);
		}

		Segment seg;
		for (int nRowIdx = 0; nRowIdx < ProtocolDataGrid->Rows->Count; nRowIdx++)
		{
			int nNumCycles = Convert::ToInt32(ProtocolDataGrid[0, nRowIdx]->Value);
			if ((nRowIdx == 0) && (!(nNumCycles > 0)))
				nNumCycles = 1;

			if (nNumCycles != 0)
			{
				seg.Clear();
				seg.SetNumCycles(nNumCycles);
			}

			Step step;
			step.SetTargetTemp((int32_t)(Convert::ToDouble(ProtocolDataGrid[2, nRowIdx]->Value) * 1000));
			step.SetHoldTimer((uint32_t)(Convert::ToDouble(ProtocolDataGrid[3, nRowIdx]->Value) * 1000));
			step.SetRampRate((int32_t)(Convert::ToDouble(ProtocolDataGrid[4, nRowIdx]->Value) * 1000));
			step.SetOpticalAcqFlg(Convert::ToBoolean(((DataGridViewCheckBoxCell^)ProtocolDataGrid[5, nRowIdx])->Value) == true);
			step.SetMeltFlg(Convert::ToBoolean(((DataGridViewCheckBoxCell^)ProtocolDataGrid[6, nRowIdx])->Value) == true);
			seg.AddStep(step);

			if ((nRowIdx >= ProtocolDataGrid->Rows->Count - 1) || (Convert::ToInt32(ProtocolDataGrid[0, nRowIdx + 1]->Value) > 0))
				pPcrProtocol->AddSegment(seg);
		}
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void NewStep_Click(System::Object^  sender, System::EventArgs^  e)
	{
		DataGridViewRow^ row = gcnew DataGridViewRow;
		ProtocolDataGrid->Rows->Add(row);
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void DeleteStep_Click(System::Object^  sender, System::EventArgs^  e)
	{
		for (int nRowIdx = ProtocolDataGrid->Rows->Count - 1; nRowIdx >= 0; nRowIdx--)
		{
			if (ProtocolDataGrid->Rows[nRowIdx]->Selected)
				ProtocolDataGrid->Rows->RemoveAt(nRowIdx);
		}
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void AddOptReadBtn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		DataGridViewRow^ row = gcnew DataGridViewRow;
		OpticalReadsGrid->Rows->Add(row);
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void DelOptReadBtn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		for (int nRowIdx = OpticalReadsGrid->Rows->Count - 1; nRowIdx >= 0; nRowIdx--)
		{
			if (OpticalReadsGrid->Rows[nRowIdx]->Selected)
				OpticalReadsGrid->Rows->RemoveAt(nRowIdx);
		}
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void SelectDataFolderButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		SelectDataFolderDlg->SelectedPath = SelectedDataFolder->Text;

		if (SelectDataFolderDlg->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			SelectedDataFolder->Text = SelectDataFolderDlg->SelectedPath;
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void RunStatusGrid_CellContentClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e)
	{
		if (e->ColumnIndex == kSelProtocolBtnIdx)
		{
			//If this site has been selected and is connected.
			int nSiteIdx = e->RowIndex;
			if (((RunStatusGrid->Rows[nSiteIdx])->Selected) && (AD_IsConnected(nSiteIdx)))
			{
				openProtocolDlg->FileName = ProtocolName->Text;
				openProtocolDlg->AddExtension = true;
				openProtocolDlg->Filter = "pcr protocols (*.qpcr)|*.qpcr|All files (*.*)|*.*";

				if (openProtocolDlg->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				{
						//Get the selected site.
						RunStatusGrid[kSelectedProtocolIdx, nSiteIdx]->Value = openProtocolDlg->FileName;
				}
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void RunStatusGrid_SelectionChanged(System::Object^  sender, System::EventArgs^  e)
	{
		bool bSelectedFound = false;
		for (int nSiteIdx = 0; nSiteIdx < RunStatusGrid->Rows->Count; nSiteIdx++)
		{
			if (((RunStatusGrid->Rows[nSiteIdx])->Selected) && (!bSelectedFound))
			{
				bSelectedFound = true;

				//Clear optical graph.
				for (int i = 0; i < ((System::Collections::Generic::IList<Series^>^)OpticalGraph->Series)->Count; i++)
				{
					Series^ series = ((System::Collections::Generic::IList<Series^>^)OpticalGraph->Series)[i];
					series->Points->Clear();
				}

				//Clear thermal graph.
				for (int i = 0; i < ((System::Collections::Generic::IList<Series^>^)ThermalGraph->Series)->Count; i++)
				{
					Series^ series = ((System::Collections::Generic::IList<Series^>^)ThermalGraph->Series)[i];
					series->Points->Clear();
				}

//				AdvancedTab->Refresh();

				//Indicate selected site.
				GraphsTab->Text = (GraphsTab->Text)->Remove(GraphsTab->Text->IndexOf("(")) + "(site " + (nSiteIdx + 1) + ")";
				AdvancedTab->Text = (AdvancedTab->Text)->Remove(AdvancedTab->Text->IndexOf("(")) + "(site " + (nSiteIdx + 1) + ")";
			}
		}

		if (!bSelectedFound)
		{
			//Indicate no site is selected.
			GraphsTab->Text = (GraphsTab->Text)->Remove(GraphsTab->Text->IndexOf("(")) + "(no selection)";
			AdvancedTab->Text = (AdvancedTab->Text)->Remove(AdvancedTab->Text->IndexOf("(")) + "(no selection)";
		}
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void AdvancedTab_TextChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		AdvancedTab_Enter(sender, e);
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void StartPcrBtn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (SelectedDataFolder->Text == "")
		{
			MessageBox::Show("Before starting, make sure a data folder is selected.");
			return;
		}

		//Make sure at least one selected site is connected and has a protocol specified.
		bool bAtLeastOneSiteReady = false;
		for (int nSiteIdx = 0; nSiteIdx < RunStatusGrid->RowCount; nSiteIdx++)
		{
			//If this site has been selected and is connected.
			if (((RunStatusGrid->Rows[nSiteIdx])->Selected) && (AD_IsConnected(nSiteIdx)))
			{
				//If this site has a protocol specified.
				if (RunStatusGrid[kSelectedProtocolIdx, nSiteIdx]->Value != nullptr)
				{
					String^ sSelProtocol = RunStatusGrid[kSelectedProtocolIdx, nSiteIdx]->Value->ToString();
					if (sSelProtocol != "")
						bAtLeastOneSiteReady = true;
				}
			}
		}

		if (bAtLeastOneSiteReady == false)
		{
			MessageBox::Show("Before starting, make sure at least one selected site is connected and has a specified protocol.");
			return;
		}

		//Do this for all selected sites.
		for (int nSiteIdx = 0; nSiteIdx < RunStatusGrid->RowCount; nSiteIdx++)
		{
			if (RunStatusGrid->Rows[nSiteIdx]->Selected)
			{
				String^ sSelProtocol = RunStatusGrid[kSelectedProtocolIdx, nSiteIdx]->Value->ToString();

				marshal_context mc;
				uint32_t nErrCode = AD_SetPcrProtocol(nSiteIdx, mc.marshal_as<LPCSTR>(sSelProtocol));
				if (nErrCode != ErrCode::kNoError)
				{
					MessageBox::Show("Could not load PCR protocol.");
				}
				else
				{
					//Send "Start" command to instrument.
					ErrCode nErrCode = (ErrCode)AD_StartRun(nSiteIdx);
					if (nErrCode != ErrCode::kNoError)
					{
						MessageBox::Show("Could not start the PCR protocol.");
					}
					else
					{
						String^ sSiteIdx = nSiteIdx.ToString();
						if (nSiteIdx < 10)
							sSiteIdx = "0" + nSiteIdx.ToString();

						DateTime^ today = DateTime::Now;
						_arOpticalDataFiles[nSiteIdx] = gcnew System::IO::StreamWriter(SelectedDataFolder->Text + "\\" + today->ToString("yyyyMMddhhmmss") + sSiteIdx + "_optical.csv");
						_arOpticalDataFiles[nSiteIdx]->WriteLine("Time (ms)" + "," +
							"Led Index" + "," +
							"Detector Index" + "," +
							"Illum. Read" + "," +
							"Dark Read" + "," +
							"Ref. Illum. Read" + "," +
							"Ref. Dark Read");
						_arThermalDataFiles[nSiteIdx] = gcnew System::IO::StreamWriter(SelectedDataFolder->Text + "\\" + today->ToString("yyyyMMddhhmmss") + sSiteIdx + "_thermal.csv");
						_arThermalDataFiles[nSiteIdx]->WriteLine("Time (ms)" + "," +
							"Block (mC)" + "," +
							"Sample (mC)" + "," +
							"unused" + "," +
							"unused" + "," +
							"Current (mA)");

						Series^ illuminatedSeries = ((System::Collections::Generic::IList<Series^>^)OpticalGraph->Series)[0];
						Series^ darkSeries = ((System::Collections::Generic::IList<Series^>^)OpticalGraph->Series)[1];
						Series^ shuttleTempSeries = ((System::Collections::Generic::IList<Series^>^)OpticalGraph->Series)[2];
						Series^ refIlluminatedSeries = ((System::Collections::Generic::IList<Series^>^)OpticalGraph->Series)[3];
						Series^ refDarkSeries = ((System::Collections::Generic::IList<Series^>^)OpticalGraph->Series)[4];
						illuminatedSeries->Points->Clear();
						darkSeries->Points->Clear();
						shuttleTempSeries->Points->Clear();
						refIlluminatedSeries->Points->Clear();
						refDarkSeries->Points->Clear();

						Series^ blockSeries = ((System::Collections::Generic::IList<Series^>^)ThermalGraph->Series)[0];
						Series^ topSeries = ((System::Collections::Generic::IList<Series^>^)ThermalGraph->Series)[1];
						Series^ currentSeries = ((System::Collections::Generic::IList<Series^>^)ThermalGraph->Series)[2];
						Series^ sampleSeries = ((System::Collections::Generic::IList<Series^>^)ThermalGraph->Series)[3];
						blockSeries->Points->Clear();
						topSeries->Points->Clear();
						sampleSeries->Points->Clear();
						currentSeries->Points->Clear();
					}
				}
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void StopPcrBtn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (MessageBox::Show("Stop selected PCR protocols?", "Confirm Stop", System::Windows::Forms::MessageBoxButtons::OKCancel) == System::Windows::Forms::DialogResult::OK)
		{
			//Send stop command to all selected sites.
			for (int nSiteIdx = 0; nSiteIdx < RunStatusGrid->RowCount; nSiteIdx++)
			{
				if ((RunStatusGrid->Rows[nSiteIdx])->Selected)
					AD_StopRun(nSiteIdx);
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void SetPidParams_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (CommPortSelection->Text == "")
			MessageBox::Show("First, select a port.");
		else
		{
			float nKp, nKi, nKd, nSlope, nYIntercept, nStabilizationTolerance_C, nStabilizationTime_s;

			bool bSelectedFound = false;
			for (int nSiteIdx = 0; nSiteIdx < AD_GetNumExpectedSites(); nSiteIdx++)
			{
				if (((RunStatusGrid->Rows[nSiteIdx])->Selected) && (!bSelectedFound))
				{
					bSelectedFound = true;
					nKp = (float)Convert::ToDouble(PidGrid[1, PidType::kTemperature]->Value);
					nKi = (float)Convert::ToDouble(PidGrid[2, PidType::kTemperature]->Value);
					nKd = (float)Convert::ToDouble(PidGrid[3, PidType::kTemperature]->Value);
					nSlope = (float)Convert::ToDouble(PidGrid[4, PidType::kTemperature]->Value);
					nYIntercept = (float)Convert::ToDouble(PidGrid[5, PidType::kTemperature]->Value);
					nStabilizationTolerance_C = (float)Convert::ToDouble(PidGrid[6, PidType::kTemperature]->Value);
					nStabilizationTime_s = (float)Convert::ToDouble(PidGrid[7, PidType::kTemperature]->Value);
					_nHostDevCommErrCode = AD_SetPidParams(nSiteIdx, PidType::kTemperature, nKp, nKi, nKd, nSlope, nYIntercept, nStabilizationTolerance_C, nStabilizationTime_s);

					nKp = (float)Convert::ToDouble(PidGrid[1, PidType::kCurrent]->Value);
					nKi = (float)Convert::ToDouble(PidGrid[2, PidType::kCurrent]->Value);
					nKd = (float)Convert::ToDouble(PidGrid[3, PidType::kCurrent]->Value);
					nSlope = (float)Convert::ToDouble(PidGrid[4, PidType::kCurrent]->Value);
					nYIntercept = (float)Convert::ToDouble(PidGrid[5, PidType::kCurrent]->Value);
					nStabilizationTolerance_C = (float)Convert::ToDouble(PidGrid[6, PidType::kCurrent]->Value);
					nStabilizationTime_s = (float)Convert::ToDouble(PidGrid[7, PidType::kCurrent]->Value);
					_nHostDevCommErrCode = AD_SetPidParams(nSiteIdx, PidType::kCurrent, nKp, nKi, nKd, nSlope, nYIntercept, nStabilizationTolerance_C, nStabilizationTime_s);
				}
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void AdvancedTab_Enter(System::Object^  sender, System::EventArgs^  e)
	{
		if (PidGrid->RowCount == 0)
		{
			PidGrid->Rows->Add(gcnew DataGridViewRow);
			PidGrid->Rows->Add(gcnew DataGridViewRow);
		}

		bool bSelectedFound = false;
		for (int nSiteIdx = 0; nSiteIdx < RunStatusGrid->Rows->Count; nSiteIdx++)
		{
			if (((RunStatusGrid->Rows[nSiteIdx])->Selected) && (!bSelectedFound))
			{
				bSelectedFound = true;
				float nKp, nKi, nKd, nSlope, nYIntercept, nStabilizationTolerance_C, nStabilizationTime_s;
				_nHostDevCommErrCode = AD_GetPidParams(nSiteIdx, PidType::kTemperature, &nKp, &nKi, &nKd, &nSlope, &nYIntercept, &nStabilizationTolerance_C, &nStabilizationTime_s);
				PidGrid[0, PidType::kTemperature]->Value = "Temperature";
				PidGrid[1, PidType::kTemperature]->Value = Convert::ToString(nKp);
				PidGrid[2, PidType::kTemperature]->Value = Convert::ToString(nKi);
				PidGrid[3, PidType::kTemperature]->Value = Convert::ToString(nKd);
				PidGrid[4, PidType::kTemperature]->Value = Convert::ToString(nSlope);
				PidGrid[5, PidType::kTemperature]->Value = Convert::ToString(nYIntercept);
				PidGrid[6, PidType::kTemperature]->Value = Convert::ToString(nStabilizationTolerance_C);
				PidGrid[7, PidType::kTemperature]->Value = Convert::ToString(nStabilizationTime_s);

				_nHostDevCommErrCode = AD_GetPidParams(nSiteIdx, PidType::kCurrent, &nKp, &nKi, &nKd, &nSlope, &nYIntercept, &nStabilizationTolerance_C, &nStabilizationTime_s);
				PidGrid[0, PidType::kCurrent]->Value = "Current";
				PidGrid[1, PidType::kCurrent]->Value = Convert::ToString(nKp);
				PidGrid[2, PidType::kCurrent]->Value = Convert::ToString(nKi);
				PidGrid[3, PidType::kCurrent]->Value = Convert::ToString(nKd);
				PidGrid[4, PidType::kCurrent]->Value = Convert::ToString(nSlope);
				PidGrid[5, PidType::kCurrent]->Value = Convert::ToString(nYIntercept);
				PidGrid[6, PidType::kCurrent]->Value = Convert::ToString(nStabilizationTolerance_C);
				PidGrid[7, PidType::kCurrent]->Value = Convert::ToString(nStabilizationTime_s);
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void DisableManControlBtn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		bool bSelectedFound = false;
		for (int nSiteIdx = 0; nSiteIdx < AD_GetNumExpectedSites(); nSiteIdx++)
		{
			if (((RunStatusGrid->Rows[nSiteIdx])->Selected) && (!bSelectedFound))
			{
				bSelectedFound = true;
				ErrCode nErrCode = (ErrCode)AD_DisableManualControl(nSiteIdx);
				if (nErrCode != ErrCode::kNoError)
					MessageBox::Show("Could not stop manual control.");
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void ActuateTemperature_Click(System::Object^  sender, System::EventArgs^  e)
	{
		bool bSelectedFound = false;
		for (int nSiteIdx = 0; nSiteIdx < AD_GetNumExpectedSites(); nSiteIdx++)
		{
			if (((RunStatusGrid->Rows[nSiteIdx])->Selected) && (!bSelectedFound))
			{
				bSelectedFound = true;
				ErrCode nErrCode = (ErrCode)AD_SetTemperatureSetpoint(nSiteIdx, (int)(Convert::ToDouble(TemperatureSetpoint->Text)));
				if (nErrCode != ErrCode::kNoError)
					MessageBox::Show("Could not start manual control.");
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void ActuateCurrent_Click(System::Object^  sender, System::EventArgs^  e)
	{
		bool bSelectedFound = false;
		for (int nSiteIdx = 0; nSiteIdx < AD_GetNumExpectedSites(); nSiteIdx++)
		{
			if (((RunStatusGrid->Rows[nSiteIdx])->Selected) && (!bSelectedFound))
			{
				bSelectedFound = true;
				ErrCode nErrCode = (ErrCode)AD_SetCurrentSetpoint(nSiteIdx, (int)(Convert::ToDouble(CurrentSetpoint->Text)));
				if (nErrCode != ErrCode::kNoError)
					MessageBox::Show("Could not start manual control.");
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void AmpDetectTab_Enter(System::Object^  sender, System::EventArgs^  e)
	{
		CommPortSelection->Items->Clear();
		array<String^>^ arPortNames = SerialPort::GetPortNames();
		CommPortSelection->Items->AddRange(arPortNames);
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void CommPortSelection_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
	{
		String^ sTemp = CommPortSelection->Text;
		int nDeviceCount = (int)DeviceCount->Value;
		if ((sTemp != "") && (nDeviceCount > 0) && (nDeviceCount <= 20))
		{
			sTemp = sTemp->Remove(0, 3); //To isolate the COM number, remove the "COM".
			AD_Uninitialize();
			AD_Initialize(Convert::ToUInt32(sTemp), nDeviceCount);
		}
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void DeviceCount_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		String^ sTemp = CommPortSelection->Text;
		int nDeviceCount = (int)DeviceCount->Value;
		if ((sTemp != "") && (nDeviceCount > 0) && (nDeviceCount <= 20))
		{
			sTemp = sTemp->Remove(0, 3); //To isolate the COM number, remove the "COM".
			AD_Uninitialize();
			AD_Initialize(Convert::ToUInt32(sTemp), nDeviceCount);
		}
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void StatusTimer_Tick(System::Object^  sender, System::EventArgs^  e)
	{
		UpdateGUI();
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void InitializeCamera(void)
	{
		cameraDll = LoadLibrary(TEXT("BaslerMultiCamera.dll"));
		if (cameraDll != NULL)
		{
			imageCaptureStatus = (GrabSucceededStatus)GetProcAddress(cameraDll, "GrabSucceededStatus");
			captureImage = (CameraCapture)GetProcAddress(cameraDll, "CameraCapture");
			cameraError = (GetCameraCaptureError)GetProcAddress(cameraDll, "GetCameraCaptureError");
			if ((NULL != imageCaptureStatus) && (NULL != captureImage) && (NULL != cameraError))
			{
				dllFuncValid = true;
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void CameraControl(int nSiteIdx)
	{
		int nError = 0;
		static uint32_t camCaptureStarted = 0;
		static bool camCaptureDone = false;
		int cameraCaptureError = 0;
		uint32_t testFlag = 0;

		// By default place nSiteIdx to 0, since there will be one site per Ampdetect unit
		if (dllFuncValid)
		{
			camCaptureDone = imageCaptureStatus();
		}

		// Check if camera capture has not started
		if (!camCaptureStarted)
		{
			// Is Paused flag set in firmware
			if (AD_GetCachedPausedFlg(nSiteIdx))
			{
				// Is software ready to take image?
				if (AD_GetCachedCaptureCameraImageFlg(nSiteIdx))
				{
					// If camera is free, initiate image capture - check camera status using camera ID
					if (camCaptureDone)
					{
						if (dllFuncValid)
						{
							camCaptureStarted = 1;
							// Send command to dll to capture image
							captureImage(AD_GetCachedCameraIdx(nSiteIdx), AD_GetCachedOpticsDetectorExposureTime(nSiteIdx), AD_GetCachedLedIntensity(nSiteIdx));
						}
					}
				}
			}
		}
		else
		{
			// Camera is done grabbing image
			if (camCaptureDone)
			{
				//Send "Pause" command to instrument.
				camCaptureStarted = 0;
				cameraCaptureError = cameraError();
				if (cameraCaptureError != 0)
				{
					MessageBox::Show("Could not find specified camera");
				}
				uint32_t nErrCode = AD_PauseRun(nSiteIdx);
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void UpdateGUI()
	{
		if (AD_GetInitializedFlg() == false)
			return;

		bool bGraphsUpdated = false;
		for (int nSiteIdx = 0; nSiteIdx < (int)AD_GetNumExpectedSites(); nSiteIdx++)
		{
			//Update DLLs system status cache object. This data comes from the specified site.
			AD_UpdateSysStatusCache(nSiteIdx);
			CameraControl(nSiteIdx);

			if (nSiteIdx >= RunStatusGrid->RowCount)
			{
				DataGridViewRow^ row = gcnew DataGridViewRow;
				RunStatusGrid->Rows->Add(row);
			}

			//Put in the site number.
			RunStatusGrid[kSiteNumIdx, nSiteIdx]->Value = Convert::ToString(nSiteIdx + 1);

			//If this site is not connected.
			if (!AD_IsConnected(nSiteIdx))
			{
				RunStatusGrid[kStateIdx, nSiteIdx]->Value = "Not Connected";
				RunStatusGrid[kSegmentIdx, nSiteIdx]->Value = "";
				RunStatusGrid[kCycleIdx, nSiteIdx]->Value = "";
				RunStatusGrid[kStepIdx, nSiteIdx]->Value = "";
				RunStatusGrid[kTimeIdx, nSiteIdx]->Value = "";
				RunStatusGrid[kTemperatureIdx, nSiteIdx]->Value = "";
			}
			else if (AD_GetCachedRunningFlg(nSiteIdx) == true) //Connected and running.
			{
				RunStatusGrid[kStateIdx, nSiteIdx]->Value = "Running";
				RunStatusGrid[kSegmentIdx, nSiteIdx]->Value = Convert::ToString(AD_GetCachedSegmentIdx(nSiteIdx) + 1);
				RunStatusGrid[kCycleIdx, nSiteIdx]->Value = Convert::ToString(AD_GetCachedCycleNum(nSiteIdx));
				RunStatusGrid[kStepIdx, nSiteIdx]->Value = Convert::ToString(AD_GetCachedStepIdx(nSiteIdx) + 1);
				RunStatusGrid[kTimeIdx, nSiteIdx]->Value = Convert::ToString((double)AD_GetCachedHoldTimer(nSiteIdx) / 1000);
				RunStatusGrid[kTemperatureIdx, nSiteIdx]->Value = Convert::ToString((double)AD_GetCachedTemperature(nSiteIdx) / 1000);
			}
			else //Connected and idle.
			{
				RunStatusGrid[kStateIdx, nSiteIdx]->Value = "Ready";
				RunStatusGrid[kSegmentIdx, nSiteIdx]->Value = "";
				RunStatusGrid[kCycleIdx, nSiteIdx]->Value = "";
				RunStatusGrid[kStepIdx, nSiteIdx]->Value = "";
				RunStatusGrid[kTimeIdx, nSiteIdx]->Value = "";
				RunStatusGrid[kTemperatureIdx, nSiteIdx]->Value = Convert::ToString((double)AD_GetCachedTemperature(nSiteIdx) / 1000);
			}

			Series^ illuminatedSeries = ((System::Collections::Generic::IList<Series^>^)OpticalGraph->Series)[0];
			Series^ darkSeries = ((System::Collections::Generic::IList<Series^>^)OpticalGraph->Series)[1];
			Series^ shuttleTempSeries = ((System::Collections::Generic::IList<Series^>^)OpticalGraph->Series)[2];
			Series^ refIlluminatedSeries = ((System::Collections::Generic::IList<Series^>^)OpticalGraph->Series)[3];
			Series^ refDarkSeries = ((System::Collections::Generic::IList<Series^>^)OpticalGraph->Series)[4];
			Series^ blockSeries = ((System::Collections::Generic::IList<Series^>^)ThermalGraph->Series)[0];
			Series^ topSeries = ((System::Collections::Generic::IList<Series^>^)ThermalGraph->Series)[1];
			Series^ currentSeries = ((System::Collections::Generic::IList<Series^>^)ThermalGraph->Series)[2];
			Series^ sampleSeries = ((System::Collections::Generic::IList<Series^>^)ThermalGraph->Series)[3];

			if (((RunStatusGrid->Rows[nSiteIdx])->Selected) && (bGraphsUpdated == false))
			{
				bGraphsUpdated = true;

				if (AD_GetCachedNumOpticsRecs(nSiteIdx) > (int)illuminatedSeries->Points->Count)
				{
					int nFirstRecToReadIdx = (uint32_t)illuminatedSeries->Points->Count;
					int nMaxRecsToRead = AD_GetCachedNumOpticsRecs(nSiteIdx) - (int)illuminatedSeries->Points->Count;
					int nNumRecsReturned = 0;
					uint32_t nErrCode = AD_UpdateOpticalRecCache(nSiteIdx, nFirstRecToReadIdx, nMaxRecsToRead, &nNumRecsReturned);
					if (nErrCode == ErrCode::kNoError)
					{
						for (int i = 0; i < nNumRecsReturned; i++)
						{
							int nCycleNum = AD_GetCachedOpticalRecCycleNum(nSiteIdx, i);
							illuminatedSeries->Points->AddXY(nCycleNum - 1, AD_GetCachedOpticalRecIlluminatedRead(nSiteIdx, i));
							darkSeries->Points->AddXY(nCycleNum - 1, AD_GetCachedOpticalRecDarkRead(nSiteIdx, i));
							shuttleTempSeries->Points->AddXY(nCycleNum - 1, 0);
							refIlluminatedSeries->Points->AddXY(nCycleNum - 1, AD_GetCachedOpticalRecRefIlluminatedRead(nSiteIdx, i));
							refDarkSeries->Points->AddXY(nCycleNum - 1, AD_GetCachedOpticalRecRefDarkRead(nSiteIdx, i));

							if (_arOpticalDataFiles[nSiteIdx] != nullptr)
							{
								_arOpticalDataFiles[nSiteIdx]->WriteLine((nCycleNum - 1) + "," +
									(AD_GetCachedOpticalRecLedIdx(nSiteIdx, i)).ToString() + "," +
									(AD_GetCachedOpticalRecDetectorIdx(nSiteIdx, i)).ToString() + "," +
									(AD_GetCachedOpticalRecIlluminatedRead(nSiteIdx, i)).ToString() + "," +
									(AD_GetCachedOpticalRecDarkRead(nSiteIdx, i)).ToString() + "," +
									(AD_GetCachedOpticalRecRefIlluminatedRead(nSiteIdx, i)).ToString() + "," +
									(AD_GetCachedOpticalRecRefDarkRead(nSiteIdx, i)).ToString());
							}
						}
					}
				}

				if (AD_GetCachedNumThermalRecs(nSiteIdx) != 0)
				{
					int nNumRecsReturned = 0;
					uint32_t nErrCode = AD_UpdateThermalRecCache(nSiteIdx, 0, AD_GetCachedNumThermalRecs(nSiteIdx), &nNumRecsReturned);
					for (int i = 0; i < nNumRecsReturned; i++)
					{
						double	nTimeTag = (double)AD_GetCachedThermalRecTimeTag(nSiteIdx, i) / 1000;
						blockSeries->Points->AddXY(nTimeTag, (double)AD_GetCachedThermalRecChan1(nSiteIdx, i) / 1000);
						sampleSeries->Points->AddXY(nTimeTag, (double)AD_GetCachedThermalRecChan2(nSiteIdx, i) / 1000);
						topSeries->Points->AddXY(nTimeTag, (double)AD_GetCachedThermalRecChan3(nSiteIdx, i) / 1000);
						currentSeries->YAxisType = DataVisualization::Charting::AxisType::Secondary;
						currentSeries->Points->AddXY(nTimeTag, (double)AD_GetCachedThermalRecCurrent(nSiteIdx, i) / 1000);

						if (_arThermalDataFiles[nSiteIdx] != nullptr)
						{
							_arThermalDataFiles[nSiteIdx]->WriteLine(nTimeTag.ToString() + "," +
								(AD_GetCachedThermalRecChan1(nSiteIdx, i)).ToString() + "," +
								(110000).ToString() + "," +
								(50000).ToString() + "," +
								(AD_GetCachedThermalRecChan4(nSiteIdx, i)).ToString() + "," +
								(AD_GetCachedThermalRecCurrent(nSiteIdx, i)).ToString());
						}
					}
				}
			}

			if (AD_GetCachedRunningFlg(nSiteIdx) == false)
			{
				if (_arOpticalDataFiles[nSiteIdx] != nullptr)
					delete (IDisposable^)(_arOpticalDataFiles[nSiteIdx]);

				if (_arThermalDataFiles[nSiteIdx] != nullptr)
					delete (IDisposable^)(_arThermalDataFiles[nSiteIdx]);
			}
		}
	}
};
}
