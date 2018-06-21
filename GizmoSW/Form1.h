#pragma once

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>


#include "PcrProtocol.h"
#include "DeviceCommDriver.h"
#include "HostMessages.h"
//#include "GizmoDLL.h"

#define BUF_SIZE 256

typedef struct {
	HANDLE hFileMap;
	void *CamCaptureDone;
	char MapName[BUF_SIZE];
	size_t size;
}CameraStatus;

using namespace System::Windows::Forms::DataVisualization::Charting;

namespace CppCLR_WinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();

#if 0
			ErrCode SharedMemInitialize();
			//Create Shared Memory
			CameraStatus camStatus;

			sprintf_s(camStatus.MapName, BUF_SIZE, "Local\\CameraCaptureDoneFlag");
			camStatus.size = 1;

			camStatus.hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE,
				NULL,
				PAGE_READWRITE,
				0,
				camStatus.size,
				camStatus.MapName);

			if (camStatus.hFileMap == NULL)
			{
				_tprintf(TEXT("Could not create file mapping object (%d).\n"), GetLastError());
			}
			else
			{
				camStatus.CamCaptureDone = MapViewOfFile(camStatus.hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, camStatus.size);
				if (camStatus.CamCaptureDone == NULL)
				{
					_tprintf(TEXT("Could not map view of file (%d).\n"), GetLastError());
					CloseHandle(camStatus.hFileMap);
				}
					
			}

			char *camData = (char*)camStatus.CamCaptureDone;

			// Write 0 to shared memory
			memset(camData, '0', camStatus.size);

			while (true)
			{
				if (*camData == '0')
				{
					std::cout << "Python Successfully wrote " << *camData << "to Shared Memory" << std::endl;
					memset(camData, '1', camStatus.size);
				}
			}
#endif
			
			

			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
			_pPcrProtocol = new PcrProtocol();
			_devCommDrv = gcnew DeviceCommDriver();
			_devCommDrv->SetPortId("COM4");
			PidSelection->SelectedIndex = 1;
			OpticsTypeCombo->SelectedIndex = 0;
			Series^ blockSeries = ((System::Collections::Generic::IList<Series^>^)ThermalGraph->Series)[0];
			blockSeries->Points->AddXY(0, 0);
			Series^ illuminatedSeries = ((System::Collections::Generic::IList<Series^>^)OpticalGraph->Series)[0];
			illuminatedSeries->Points->AddXY(0, 45000);

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

			delete _pPcrProtocol;
		}
	private: System::Windows::Forms::TabControl^  GizmoTabs;
	private: System::Windows::Forms::TabPage^  GizmoTab;
	private: System::Windows::Forms::TabPage^  ProtocolsTab;
	private: System::UInt32				_nHostDevCommErrCode = ErrCode::kDeviceCommErr;
	private: System::IO::StreamWriter^			_opticalDataFile;
	private: System::IO::StreamWriter^			_thermalDataFile;
	protected:

	protected:

	protected:


	private: System::Windows::Forms::Button^  SaveProtocol;
	private: System::Windows::Forms::DataGridView^  ProtocolDataGrid;
	private: System::Windows::Forms::RichTextBox^  ProtocolName;
	private: PcrProtocol* _pPcrProtocol;
	private: DeviceCommDriver ^ _devCommDrv;


















	private: System::Windows::Forms::Button^  OpenProtocol;
	private: System::Windows::Forms::Button^  NewStep;
	private: System::Windows::Forms::OpenFileDialog^  openProtocolDlg;


























	private: System::Windows::Forms::Button^  DeleteStep;
	private: System::Windows::Forms::SaveFileDialog^  saveProtocolDlg;
	private: System::Windows::Forms::Button^  SelectProtocolBtn;
	private: System::Windows::Forms::RichTextBox^  SelectedProtocol;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  StopPcrBtn;
	private: System::Windows::Forms::Button^  RunPcrBtn;
	private: System::Windows::Forms::TabPage^  AdvancedTab;



private: System::Windows::Forms::DataGridView^  RunStatusGrid;





private: System::Windows::Forms::Timer^  StatusTimer;







private: System::Windows::Forms::ComboBox^  CommPortSelection;
private: System::Windows::Forms::Label^  label2;
private: System::Windows::Forms::ComboBox^  PidSelection;
private: System::Windows::Forms::Label^  label3;







private: System::Windows::Forms::DataVisualization::Charting::Chart^  ThermalGraph;
private: System::Windows::Forms::DataVisualization::Charting::Chart^  OpticalGraph;

private: System::Windows::Forms::Label^  label4;
private: System::Windows::Forms::Button^  SelectDataFolderButton;
private: System::Windows::Forms::RichTextBox^  SelectedDataFolder;

private: System::Windows::Forms::FolderBrowserDialog^  SelectDataFolderDlg;
private: System::Windows::Forms::Button^  ActuateSetpoint;

private: System::Windows::Forms::Label^  label5;
private: System::Windows::Forms::TextBox^  ManControlSetpoint;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  SiteCol;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  ActiveCol;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  SegmentCol;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  CycleCol;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  StepCol;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  StepTimeCol;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  TemperatureCol;























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
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea5 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend5 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series19 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series20 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series21 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series22 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea6 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend6 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series23 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series24 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series25 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series26 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series27 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->GizmoTabs = (gcnew System::Windows::Forms::TabControl());
			this->GizmoTab = (gcnew System::Windows::Forms::TabPage());
			this->SelectDataFolderButton = (gcnew System::Windows::Forms::Button());
			this->SelectedDataFolder = (gcnew System::Windows::Forms::RichTextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->ThermalGraph = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->OpticalGraph = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->PidSelection = (gcnew System::Windows::Forms::ComboBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->CommPortSelection = (gcnew System::Windows::Forms::ComboBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->RunStatusGrid = (gcnew System::Windows::Forms::DataGridView());
			this->SiteCol = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ActiveCol = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->SegmentCol = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->CycleCol = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->StepCol = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->StepTimeCol = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->TemperatureCol = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->SelectProtocolBtn = (gcnew System::Windows::Forms::Button());
			this->SelectedProtocol = (gcnew System::Windows::Forms::RichTextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->StopPcrBtn = (gcnew System::Windows::Forms::Button());
			this->RunPcrBtn = (gcnew System::Windows::Forms::Button());
			this->ProtocolsTab = (gcnew System::Windows::Forms::TabPage());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->DelOptReadBtn = (gcnew System::Windows::Forms::Button());
			this->AddOptReadBtn = (gcnew System::Windows::Forms::Button());
			this->OpticalReadsGrid = (gcnew System::Windows::Forms::DataGridView());
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
			this->ActuateSetpoint = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->ManControlSetpoint = (gcnew System::Windows::Forms::TextBox());
			this->openProtocolDlg = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveProtocolDlg = (gcnew System::Windows::Forms::SaveFileDialog());
			this->StatusTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->SelectDataFolderDlg = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->LEDIndex = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->LedIntensity = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->LedStabilizationTime = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->DetectorIndex = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->RefDetectorIndex = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->DetectorIntegrationTime = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->GizmoTabs->SuspendLayout();
			this->GizmoTab->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ThermalGraph))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->OpticalGraph))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RunStatusGrid))->BeginInit();
			this->ProtocolsTab->SuspendLayout();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->OpticalReadsGrid))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ProtocolDataGrid))->BeginInit();
			this->AdvancedTab->SuspendLayout();
			this->SuspendLayout();
			// 
			// GizmoTabs
			// 
			this->GizmoTabs->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->GizmoTabs->Controls->Add(this->GizmoTab);
			this->GizmoTabs->Controls->Add(this->ProtocolsTab);
			this->GizmoTabs->Controls->Add(this->AdvancedTab);
			this->GizmoTabs->Location = System::Drawing::Point(9, 10);
			this->GizmoTabs->Margin = System::Windows::Forms::Padding(2);
			this->GizmoTabs->Name = L"GizmoTabs";
			this->GizmoTabs->SelectedIndex = 0;
			this->GizmoTabs->Size = System::Drawing::Size(886, 606);
			this->GizmoTabs->TabIndex = 0;
			// 
			// GizmoTab
			// 
			this->GizmoTab->Controls->Add(this->SelectDataFolderButton);
			this->GizmoTab->Controls->Add(this->SelectedDataFolder);
			this->GizmoTab->Controls->Add(this->label4);
			this->GizmoTab->Controls->Add(this->ThermalGraph);
			this->GizmoTab->Controls->Add(this->OpticalGraph);
			this->GizmoTab->Controls->Add(this->PidSelection);
			this->GizmoTab->Controls->Add(this->label3);
			this->GizmoTab->Controls->Add(this->CommPortSelection);
			this->GizmoTab->Controls->Add(this->label2);
			this->GizmoTab->Controls->Add(this->RunStatusGrid);
			this->GizmoTab->Controls->Add(this->SelectProtocolBtn);
			this->GizmoTab->Controls->Add(this->SelectedProtocol);
			this->GizmoTab->Controls->Add(this->label1);
			this->GizmoTab->Controls->Add(this->StopPcrBtn);
			this->GizmoTab->Controls->Add(this->RunPcrBtn);
			this->GizmoTab->Location = System::Drawing::Point(4, 22);
			this->GizmoTab->Margin = System::Windows::Forms::Padding(2);
			this->GizmoTab->Name = L"GizmoTab";
			this->GizmoTab->Padding = System::Windows::Forms::Padding(2);
			this->GizmoTab->Size = System::Drawing::Size(878, 580);
			this->GizmoTab->TabIndex = 0;
			this->GizmoTab->Text = L"Gizmo";
			this->GizmoTab->UseVisualStyleBackColor = true;
			this->GizmoTab->Enter += gcnew System::EventHandler(this, &Form1::GizmoTab_Enter);
			// 
			// SelectDataFolderButton
			// 
			this->SelectDataFolderButton->Location = System::Drawing::Point(390, 50);
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
			this->SelectedDataFolder->Location = System::Drawing::Point(81, 50);
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
			this->label4->Location = System::Drawing::Point(4, 52);
			this->label4->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(65, 13);
			this->label4->TabIndex = 12;
			this->label4->Text = L"Data Folder:";
			// 
			// ThermalGraph
			// 
			this->ThermalGraph->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->ThermalGraph->BorderlineColor = System::Drawing::Color::Black;
			chartArea5->AxisY->Maximum = 100000;
			chartArea5->AxisY->Minimum = 50000;
			chartArea5->Name = L"ChartArea1";
			this->ThermalGraph->ChartAreas->Add(chartArea5);
			legend5->Name = L"Legend1";
			this->ThermalGraph->Legends->Add(legend5);
			this->ThermalGraph->Location = System::Drawing::Point(7, 418);
			this->ThermalGraph->Margin = System::Windows::Forms::Padding(2);
			this->ThermalGraph->Name = L"ThermalGraph";
			series19->ChartArea = L"ChartArea1";
			series19->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series19->Legend = L"Legend1";
			series19->Name = L"Block";
			series20->ChartArea = L"ChartArea1";
			series20->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series20->Legend = L"Legend1";
			series20->Name = L"Top Heater";
			series21->ChartArea = L"ChartArea1";
			series21->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series21->Legend = L"Legend1";
			series21->Name = L"Current";
			series22->ChartArea = L"ChartArea1";
			series22->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series22->Legend = L"Legend1";
			series22->Name = L"Sample";
			this->ThermalGraph->Series->Add(series19);
			this->ThermalGraph->Series->Add(series20);
			this->ThermalGraph->Series->Add(series21);
			this->ThermalGraph->Series->Add(series22);
			this->ThermalGraph->Size = System::Drawing::Size(857, 159);
			this->ThermalGraph->TabIndex = 11;
			this->ThermalGraph->Text = L"Thermal Data";
			// 
			// OpticalGraph
			// 
			this->OpticalGraph->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			chartArea6->Name = L"ChartArea1";
			this->OpticalGraph->ChartAreas->Add(chartArea6);
			legend6->Name = L"Legend1";
			this->OpticalGraph->Legends->Add(legend6);
			this->OpticalGraph->Location = System::Drawing::Point(7, 240);
			this->OpticalGraph->Margin = System::Windows::Forms::Padding(2);
			this->OpticalGraph->Name = L"OpticalGraph";
			series23->ChartArea = L"ChartArea1";
			series23->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series23->Legend = L"Legend1";
			series23->Name = L"Illuminated";
			series24->ChartArea = L"ChartArea1";
			series24->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series24->Legend = L"Legend1";
			series24->Name = L"Dark";
			series25->ChartArea = L"ChartArea1";
			series25->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series25->Legend = L"Legend1";
			series25->Name = L"Temperature";
			series26->ChartArea = L"ChartArea1";
			series26->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series26->Legend = L"Legend1";
			series26->Name = L"RefIlluminated";
			series27->ChartArea = L"ChartArea1";
			series27->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series27->Legend = L"Legend1";
			series27->Name = L"RefDark";
			this->OpticalGraph->Series->Add(series23);
			this->OpticalGraph->Series->Add(series24);
			this->OpticalGraph->Series->Add(series25);
			this->OpticalGraph->Series->Add(series26);
			this->OpticalGraph->Series->Add(series27);
			this->OpticalGraph->Size = System::Drawing::Size(857, 149);
			this->OpticalGraph->TabIndex = 10;
			this->OpticalGraph->Text = L"Optical Data";
			this->OpticalGraph->Click += gcnew System::EventHandler(this, &Form1::OpticalGraph_Click);
			// 
			// PidSelection
			// 
			this->PidSelection->AllowDrop = true;
			this->PidSelection->FormattingEnabled = true;
			this->PidSelection->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Meerstetter", L"Homegrown" });
			this->PidSelection->Location = System::Drawing::Point(268, 115);
			this->PidSelection->Margin = System::Windows::Forms::Padding(2);
			this->PidSelection->Name = L"PidSelection";
			this->PidSelection->Size = System::Drawing::Size(119, 21);
			this->PidSelection->TabIndex = 9;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(238, 118);
			this->label3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(28, 13);
			this->label3->TabIndex = 8;
			this->label3->Text = L"PID:";
			// 
			// CommPortSelection
			// 
			this->CommPortSelection->AllowDrop = true;
			this->CommPortSelection->FormattingEnabled = true;
			this->CommPortSelection->Location = System::Drawing::Point(81, 115);
			this->CommPortSelection->Margin = System::Windows::Forms::Padding(2);
			this->CommPortSelection->Name = L"CommPortSelection";
			this->CommPortSelection->Size = System::Drawing::Size(119, 21);
			this->CommPortSelection->TabIndex = 7;
			this->CommPortSelection->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::CommPortSelection_SelectedIndexChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(4, 118);
			this->label2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(61, 13);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Comm Port:";
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
			this->RunStatusGrid->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(7) {
				this->SiteCol,
					this->ActiveCol, this->SegmentCol, this->CycleCol, this->StepCol, this->StepTimeCol, this->TemperatureCol
			});
			this->RunStatusGrid->Location = System::Drawing::Point(450, 7);
			this->RunStatusGrid->Margin = System::Windows::Forms::Padding(2);
			this->RunStatusGrid->MultiSelect = false;
			this->RunStatusGrid->Name = L"RunStatusGrid";
			this->RunStatusGrid->ReadOnly = true;
			this->RunStatusGrid->RowHeadersVisible = false;
			this->RunStatusGrid->RowTemplate->Height = 24;
			this->RunStatusGrid->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->RunStatusGrid->Size = System::Drawing::Size(414, 199);
			this->RunStatusGrid->TabIndex = 5;
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
			this->ActiveCol->MinimumWidth = 20;
			this->ActiveCol->Name = L"ActiveCol";
			this->ActiveCol->ReadOnly = true;
			this->ActiveCol->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->ActiveCol->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->ActiveCol->Width = 20;
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
			// SelectProtocolBtn
			// 
			this->SelectProtocolBtn->Location = System::Drawing::Point(390, 7);
			this->SelectProtocolBtn->Margin = System::Windows::Forms::Padding(2);
			this->SelectProtocolBtn->Name = L"SelectProtocolBtn";
			this->SelectProtocolBtn->Size = System::Drawing::Size(32, 26);
			this->SelectProtocolBtn->TabIndex = 4;
			this->SelectProtocolBtn->Text = L"...";
			this->SelectProtocolBtn->UseVisualStyleBackColor = true;
			this->SelectProtocolBtn->Click += gcnew System::EventHandler(this, &Form1::SelectProtocolBtn_Click);
			// 
			// SelectedProtocol
			// 
			this->SelectedProtocol->Location = System::Drawing::Point(81, 7);
			this->SelectedProtocol->Margin = System::Windows::Forms::Padding(2);
			this->SelectedProtocol->Multiline = false;
			this->SelectedProtocol->Name = L"SelectedProtocol";
			this->SelectedProtocol->ReadOnly = true;
			this->SelectedProtocol->Size = System::Drawing::Size(306, 27);
			this->SelectedProtocol->TabIndex = 3;
			this->SelectedProtocol->Text = L"";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(4, 14);
			this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(74, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"PCR Protocol:";
			// 
			// StopPcrBtn
			// 
			this->StopPcrBtn->Location = System::Drawing::Point(240, 180);
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
			this->RunPcrBtn->Location = System::Drawing::Point(22, 180);
			this->RunPcrBtn->Margin = System::Windows::Forms::Padding(2);
			this->RunPcrBtn->Name = L"RunPcrBtn";
			this->RunPcrBtn->Size = System::Drawing::Size(56, 26);
			this->RunPcrBtn->TabIndex = 0;
			this->RunPcrBtn->Text = L"Run";
			this->RunPcrBtn->UseVisualStyleBackColor = true;
			this->RunPcrBtn->Click += gcnew System::EventHandler(this, &Form1::RunPcrBtn_Click);
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
			this->ProtocolsTab->Size = System::Drawing::Size(878, 580);
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
			this->OpticalReadsGrid->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form1::OpticalReadsGrid_CellContentClick);
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
			this->ProtocolDataGrid->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
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
			this->AdvancedTab->Controls->Add(this->ActuateSetpoint);
			this->AdvancedTab->Controls->Add(this->label5);
			this->AdvancedTab->Controls->Add(this->ManControlSetpoint);
			this->AdvancedTab->Location = System::Drawing::Point(4, 22);
			this->AdvancedTab->Margin = System::Windows::Forms::Padding(2);
			this->AdvancedTab->Name = L"AdvancedTab";
			this->AdvancedTab->Size = System::Drawing::Size(878, 580);
			this->AdvancedTab->TabIndex = 2;
			this->AdvancedTab->Text = L"Advanced";
			this->AdvancedTab->UseVisualStyleBackColor = true;
			// 
			// ActuateSetpoint
			// 
			this->ActuateSetpoint->Location = System::Drawing::Point(88, 41);
			this->ActuateSetpoint->Margin = System::Windows::Forms::Padding(2);
			this->ActuateSetpoint->Name = L"ActuateSetpoint";
			this->ActuateSetpoint->Size = System::Drawing::Size(56, 19);
			this->ActuateSetpoint->TabIndex = 2;
			this->ActuateSetpoint->Text = L"Actuate";
			this->ActuateSetpoint->UseVisualStyleBackColor = true;
			this->ActuateSetpoint->Click += gcnew System::EventHandler(this, &Form1::ActuateSetpoint_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(2, 25);
			this->label5->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(46, 13);
			this->label5->TabIndex = 1;
			this->label5->Text = L"Setpoint";
			// 
			// ManControlSetpoint
			// 
			this->ManControlSetpoint->Location = System::Drawing::Point(2, 41);
			this->ManControlSetpoint->Margin = System::Windows::Forms::Padding(2);
			this->ManControlSetpoint->Name = L"ManControlSetpoint";
			this->ManControlSetpoint->Size = System::Drawing::Size(72, 20);
			this->ManControlSetpoint->TabIndex = 0;
			// 
			// StatusTimer
			// 
			this->StatusTimer->Enabled = true;
			this->StatusTimer->Tick += gcnew System::EventHandler(this, &Form1::StatusTimer_Tick);
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
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(904, 626);
			this->Controls->Add(this->GizmoTabs);
			this->Name = L"Form1";
			this->Text = L"Gizmo";
			this->GizmoTabs->ResumeLayout(false);
			this->GizmoTab->ResumeLayout(false);
			this->GizmoTab->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ThermalGraph))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->OpticalGraph))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RunStatusGrid))->EndInit();
			this->ProtocolsTab->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->OpticalReadsGrid))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ProtocolDataGrid))->EndInit();
			this->AdvancedTab->ResumeLayout(false);
			this->AdvancedTab->PerformLayout();
			this->ResumeLayout(false);

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

			*_pPcrProtocol << arTemp;
			WritePcrProtocolToGui();
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

		if (saveProtocolDlg->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			ReadPcrProtocolFromGui();
			ProtocolName->Text = saveProtocolDlg->FileName;
			System::IO::StreamWriter^ file = gcnew System::IO::StreamWriter(ProtocolName->Text);
			System::IO::BinaryWriter^ binFile = gcnew System::IO::BinaryWriter(file->BaseStream);

			uint8_t arTemp[5 * 1024];
			*_pPcrProtocol >> arTemp;
			array<uint8_t>^ protocolBuf = gcnew array<uint8_t>(_pPcrProtocol->GetStreamSize());
			for (int i = 0; i < (int)_pPcrProtocol->GetStreamSize(); i++)
				protocolBuf[i] = arTemp[i];

			binFile->BaseStream->SetLength(0);
			binFile->Write(protocolBuf);
			binFile->Close();
		}
		WritePcrProtocolToGui();
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void WritePcrProtocolToGui()
	{
		ProtocolDataGrid->Rows->Clear();
		OpticalReadsGrid->Rows->Clear();

		//Iterate through all optical reads in this protocol.
		OpticsTypeCombo->SelectedIndex = _pPcrProtocol->GetDetectorType();
		for (int i = 0; i < (int)_pPcrProtocol->GetNumOpticalReads(); i++)
		{
			DataGridViewRow^ row = gcnew DataGridViewRow;
			OpticalReadsGrid->Rows->Add(row);
			int nRowIdx = OpticalReadsGrid->RowCount - 1;
			OpticalRead optRead = _pPcrProtocol->GetOpticalRead(i);

			OpticalReadsGrid[0, nRowIdx]->Value = optRead.GetLedIdx();
			OpticalReadsGrid[1, nRowIdx]->Value = optRead.GetLedIntensity();
			OpticalReadsGrid[2, nRowIdx]->Value = optRead.GetLedStablizationTime();
			OpticalReadsGrid[3, nRowIdx]->Value = optRead.GetDetectorIdx();
			OpticalReadsGrid[4, nRowIdx]->Value = optRead.GetReferenceIdx();
			OpticalReadsGrid[5, nRowIdx]->Value = optRead.GetDetectorIntegrationTime();
		}

		//Iterate through all segments in this protocol.
		for (int nSegIdx = 0; nSegIdx < (int)_pPcrProtocol->GetNumSegs(); nSegIdx++)
		{
			Segment seg = _pPcrProtocol->GetSegment(nSegIdx);

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
	private: System::Void ReadPcrProtocolFromGui()
	{
		_pPcrProtocol->Clear();

		OpticalRead optRead;
		for (int nRowIdx = 0; nRowIdx < OpticalReadsGrid->Rows->Count; nRowIdx++)
		{
			optRead.SetLedIdx(Convert::ToInt32(OpticalReadsGrid[0, nRowIdx]->Value));
			optRead.SetLedIntensity(Convert::ToInt32(OpticalReadsGrid[1, nRowIdx]->Value));
			optRead.SetLedStablizationTime(Convert::ToInt32(OpticalReadsGrid[2, nRowIdx]->Value));
			optRead.SetDetectorIdx(Convert::ToInt32(OpticalReadsGrid[3, nRowIdx]->Value));
			optRead.SetReferenceIdx(Convert::ToInt32(OpticalReadsGrid[4, nRowIdx]->Value));
			optRead.SetDetectorIntegrationTime(Convert::ToInt32(OpticalReadsGrid[5, nRowIdx]->Value));
			_pPcrProtocol->AddOpticalRead(optRead);
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
				_pPcrProtocol->AddSegment(seg);
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
	private: System::Void SelectProtocolBtn_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		openProtocolDlg->FileName = ProtocolName->Text;
		openProtocolDlg->AddExtension = true;
		openProtocolDlg->Filter = "pcr protocols (*.qpcr)|*.qpcr|All files (*.*)|*.*";

		if (openProtocolDlg->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			SelectedProtocol->Text = openProtocolDlg->FileName;
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void SelectDataFolderButton_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		SelectDataFolderDlg->SelectedPath = SelectedDataFolder->Text;

		if (SelectDataFolderDlg->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			SelectedDataFolder->Text = SelectDataFolderDlg->SelectedPath;
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void RunPcrBtn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (SelectedProtocol->Text == "")
		{
			MessageBox::Show("First, select a protocol.");
		}
		else if (CommPortSelection->SelectedItem == nullptr)
		{
			MessageBox::Show("First, select a port.");
		}
		else if (SelectedDataFolder->Text == "")
		{
			MessageBox::Show("First, select a data folder.");
		}
		else if (PidSelection->SelectedItem == nullptr)
		{
			MessageBox::Show("First, select a PID.");
		}
		else if (_nHostDevCommErrCode != ErrCode::kNoError)
		{
			MessageBox::Show("Not connected to device.");
		}
		else
		{
			System::IO::StreamReader^ file = gcnew System::IO::StreamReader(SelectedProtocol->Text);
			System::IO::BinaryReader^ binFile = gcnew System::IO::BinaryReader(file->BaseStream);

			uint8_t arTemp[5 * 1024];
			array<uint8_t>^ protocolBuf = binFile->ReadBytes(sizeof(arTemp));
			for (int i = 0; i < binFile->BaseStream->Length; i++)
				arTemp[i] = protocolBuf[i];
			*_pPcrProtocol << arTemp;
			binFile->Close();

			LoadPcrProtocolReq loadReq;
			HostMsg response;
			loadReq.SetSiteIdx(0);
			loadReq.SetPcrProtocol(*_pPcrProtocol);

			//Send selected PCR protocol to instrument.
			uint32_t nErrCode = _devCommDrv->MsgTransaction(loadReq, &response);
			if (nErrCode != ErrCode::kNoError)
			{
				MessageBox::Show("Could not load PCR protocol.");
			}
			else
			{
				//Send "Start" command to instrument.
				StartRunReq startReq;
				startReq.SetSiteIdx(0);
				startReq.SetMeerstetterPidFlg(PidSelection->SelectedIndex != 1);
				startReq.SetMsgSize(startReq.GetStreamSize());
				nErrCode = _devCommDrv->MsgTransaction(startReq, &response);
				if (nErrCode != ErrCode::kNoError)
				{
					MessageBox::Show("Could not start the PCR protocol.");
				}
				else
				{
					DateTime^ today = DateTime::Now;
					_opticalDataFile = gcnew System::IO::StreamWriter(SelectedDataFolder->Text + "\\" + today->ToString("yyyyMMddhhmmss") + "_optical.csv");
					_thermalDataFile = gcnew System::IO::StreamWriter(SelectedDataFolder->Text + "\\" + today->ToString("yyyyMMddhhmmss") + "_thermal.csv");

					Series^ illuminatedSeries = ((System::Collections::Generic::IList<Series^>^)OpticalGraph->Series)[0];
					Series^ darkSeries = ((System::Collections::Generic::IList<Series^>^)OpticalGraph->Series)[1];
					Series^ shuttleTempSeries = ((System::Collections::Generic::IList<Series^>^)OpticalGraph->Series)[2];
					illuminatedSeries->Points->Clear();
					darkSeries->Points->Clear();
					shuttleTempSeries->Points->Clear();

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

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void StopPcrBtn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (CommPortSelection->SelectedItem == nullptr)
		{
			MessageBox::Show("First, select a port.");
		}
		else if (_nHostDevCommErrCode != ErrCode::kNoError)
		{
			MessageBox::Show("Not connected to device.");
		}
		else
		{
			if (MessageBox::Show("Stop PCR protocol?", "Confirm Stop", System::Windows::Forms::MessageBoxButtons::OKCancel) == System::Windows::Forms::DialogResult::OK)
			{
				//Send "Stop" command to instrument.
				StopRunReq request;
				HostMsg response;
				request.SetSiteIdx(0);
				request.SetMsgSize(request.GetStreamSize());
				uint32_t nErrCode = _devCommDrv->MsgTransaction(request, &response);
				if (nErrCode != ErrCode::kNoError)
					MessageBox::Show("Could not stop the PCR protocol.");
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void ActuateSetpoint_Click(System::Object^  sender, System::EventArgs^  e)
	{
		SetManControlSetpointReq	request;
		HostMsg						response;

		request.SetSiteIdx(0);
		request.SetSetpoint((int32_t)(Convert::ToDouble(ManControlSetpoint->Text) * 1000));
		request.SetMsgSize(request.GetStreamSize());
		uint32_t nErrCode = _devCommDrv->MsgTransaction(request, &response);
		if (nErrCode != ErrCode::kNoError)
		{
			MessageBox::Show("Could not start manual control.");
		}
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void GizmoTab_Enter(System::Object^  sender, System::EventArgs^  e) 
	{
		CommPortSelection->Items->Clear();
		array<String^>^ arPortNames = SerialPort::GetPortNames();
		CommPortSelection->Items->AddRange(arPortNames);
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void StatusTimer_Tick(System::Object^  sender, System::EventArgs^  e)
	{
		HostMsg			request(HostMsg::MakeObjId('G', 'S', 't', 't'));
		GetStatusRes	response;

		_nHostDevCommErrCode = _devCommDrv->MsgTransaction(request, &response);
		UpdateGUI(response);
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void CommPortSelection_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		_devCommDrv->SetPortId(CommPortSelection->Text);
	}

	/////////////////////////////////////////////////////////////////////////////////
	private: System::Void UpdateGUI(GetStatusRes& statusResponse)
	{
		if (_nHostDevCommErrCode != ErrCode::kNoError)
		{
			if (_opticalDataFile != nullptr)
			{
				delete (IDisposable^)(_opticalDataFile);
				_opticalDataFile = nullptr;
			}
			if (_thermalDataFile != nullptr)
			{
				delete (IDisposable^)(_thermalDataFile);
				_thermalDataFile = nullptr;
			}
			return;
		}

		const SysStatus* pSysStatus = statusResponse.GetSysStatusPtr();
		for (int nSiteIdx = 0; nSiteIdx < (int)pSysStatus->GetNumSites(); nSiteIdx++)
		{
			if (nSiteIdx >= RunStatusGrid->RowCount)
			{
				DataGridViewRow^ row = gcnew DataGridViewRow;
				RunStatusGrid->Rows->Add(row);
			}

			const SiteStatus& siteStatus = pSysStatus->GetSiteStatus(nSiteIdx);
			RunStatusGrid[0, nSiteIdx]->Value = Convert::ToString(nSiteIdx + 1);
			RunStatusGrid[1, nSiteIdx]->Value = siteStatus.GetRunningFlg() ? "Y" : "N";
			if (siteStatus.GetRunningFlg() == true)
			{
				RunStatusGrid[2, nSiteIdx]->Value = Convert::ToString(siteStatus.GetSegmentIdx() + 1);
				RunStatusGrid[3, nSiteIdx]->Value = Convert::ToString(siteStatus.GetCycle() + 1);
				RunStatusGrid[4, nSiteIdx]->Value = Convert::ToString(siteStatus.GetStepIdx() + 1);
				RunStatusGrid[5, nSiteIdx]->Value = Convert::ToString((double)siteStatus.GetHoldTimer() / 1000);
				RunStatusGrid[6, nSiteIdx]->Value = Convert::ToString((double)siteStatus.GetTemperature() / 1000);
			}
			else
			{
				RunStatusGrid[2, nSiteIdx]->Value = "";
				RunStatusGrid[3, nSiteIdx]->Value = "";
				RunStatusGrid[4, nSiteIdx]->Value = "";
				RunStatusGrid[5, nSiteIdx]->Value = "";
				RunStatusGrid[6, nSiteIdx]->Value = "";
			}

			Series^ illuminatedSeries = ((System::Collections::Generic::IList<Series^>^)OpticalGraph->Series)[0];
			Series^ darkSeries = ((System::Collections::Generic::IList<Series^>^)OpticalGraph->Series)[1];
			Series^ shuttleTempSeries = ((System::Collections::Generic::IList<Series^>^)OpticalGraph->Series)[2];
			Series^ refIlluminatedSeries = ((System::Collections::Generic::IList<Series^>^)OpticalGraph->Series)[3];
			Series^ refDarkSeries = ((System::Collections::Generic::IList<Series^>^)OpticalGraph->Series)[4];
			if (siteStatus.GetNumOpticsRecs() > (uint32_t)illuminatedSeries->Points->Count)
			{
				GetOpticsRecsReq	request;
				GetOpticsRecsRes	response;
				request.SetSiteIdx(0);
				request.SetFirstRecToReadIdx((uint32_t)illuminatedSeries->Points->Count);
				request.SetNumRecsToRead(1);
				uint32_t nErrCode = _devCommDrv->MsgTransaction(request, &response);

				if (nErrCode == ErrCode::kNoError)
				{
					//OpticsRec optRec = response.GetOpticsRec(0);
					//optRec = siteStatus.GetOpticalRec(i);
					OpticsRec optRec;
					for (int i = 0; i < (int)response.GetNumOpticsRecs(); i++)
					{
						optRec = response.GetOpticsRec(i);
						illuminatedSeries->Points->AddXY(optRec._nCycleIdx + 1, optRec._nIlluminatedRead);
						darkSeries->Points->AddXY(optRec._nCycleIdx + 1, optRec._nDarkRead);
						shuttleTempSeries->Points->AddXY(optRec._nCycleIdx + 1, optRec._nShuttleTemp_mC);
						refIlluminatedSeries->Points->AddXY(optRec._nCycleIdx + 1, optRec._nRefIlluminatedRead);
						refDarkSeries->Points->AddXY(optRec._nCycleIdx + 1, optRec._nRefDarkRead);

						if (_opticalDataFile != nullptr)
						{
							_opticalDataFile->WriteLine(optRec._nCycleIdx + "," +
								optRec._nLedIdx.ToString() + "," +
								optRec._nDetectorIdx.ToString() + "," +
								optRec._nIlluminatedRead.ToString() + "," +
								optRec._nDarkRead.ToString() + "," +
								optRec._nRefIlluminatedRead.ToString() + "," +
								optRec._nRefDarkRead.ToString());
						}
					}
					
				}
			}

			if (siteStatus.GetNumThermalRecs() != 0)
			{
				Series^ blockSeries = ((System::Collections::Generic::IList<Series^>^)ThermalGraph->Series)[0];
				Series^ topSeries = ((System::Collections::Generic::IList<Series^>^)ThermalGraph->Series)[1];
				Series^ currentSeries = ((System::Collections::Generic::IList<Series^>^)ThermalGraph->Series)[2];
				Series^ sampleSeries = ((System::Collections::Generic::IList<Series^>^)ThermalGraph->Series)[3];

				HostMsg				request(StreamingObj::MakeObjId('G', 'T', 'h', 'm'));
				GetThermalRecsRes	response;
				uint32_t nErrCode = _devCommDrv->MsgTransaction(request, &response);

				ThermalRec thermRec;
				for (int i = 0; i < (int)response.GetNumThermalRecs(); i++)
				{
					thermRec = response.GetThermalRec(i);
					blockSeries->Points->AddXY(thermRec._nTimeTag_ms, thermRec._nChan1_mC);
					sampleSeries->Points->AddXY(thermRec._nTimeTag_ms, thermRec._nChan4_mC);
					topSeries->Points->AddXY(thermRec._nTimeTag_ms, thermRec._nChan3_mC);
					currentSeries->Points->AddXY(thermRec._nTimeTag_ms, thermRec._nCurrent_mA);

					if (_thermalDataFile != nullptr)
					{
						_thermalDataFile->WriteLine(thermRec._nTimeTag_ms.ToString() + "," +
							thermRec._nChan1_mC.ToString() + "," +
							thermRec._nChan2_mC.ToString() + "," +
							thermRec._nChan3_mC.ToString() + "," +
							thermRec._nChan4_mC.ToString() + "," +
							thermRec._nCurrent_mA.ToString());
					}
				}
			}

			if (siteStatus.GetRunningFlg() == false)
			{
				if (_opticalDataFile != nullptr)
					delete (IDisposable^)(_opticalDataFile);

				if (_thermalDataFile != nullptr)
					delete (IDisposable^)(_thermalDataFile);
			}
		}
	}
private: System::Void saveProtocolDlg_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
}
private: System::Void SelectDataFolderDlg_HelpRequest(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void OpticalGraph_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void OpticalReadsGrid_CellContentClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
}
};
}
