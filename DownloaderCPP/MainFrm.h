#pragma once
#include <string>

////#define DEBUG

namespace DownloaderCPP {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO::Ports;
	using namespace System::IO;
	using namespace System::Net;
	using namespace System::Net::Security;
	using namespace System::Security::Cryptography::X509Certificates;
	using namespace System::Text;
	using namespace System::Threading;
	using namespace System::Collections::Generic;
	
	/// <summary>
	/// Podsumowanie informacji o MainFrm
	/// </summary>
	public ref class MainFrm : public System::Windows::Forms::Form
	{
	private:
		String^ adress = "http://biotronika.pl/downloader.php?nodeid=";
		array<String^>^ serialPorts = nullptr;
		static List<String^>^ comPortResults = nullptr;
		List<String^>^ therapy = nullptr;
		bool myError;
		String^ fileName;
		static SerialPort^ _serialPort;
		const int STARTUP_TIME = 5000;

	private: System::Windows::Forms::Label^  lbPort;
	private: System::Windows::Forms::ComboBox^  cbPort;
	private: System::Windows::Forms::Button^  btnDownload;

	private: System::Windows::Forms::TextBox^  tbInformacja;

	private: System::Windows::Forms::Timer^  tmClose;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Button^  btnLIst;
	private: System::Windows::Forms::ToolTip^  toolTip1;
	private: System::Windows::Forms::NumericUpDown^  bankSelector;


	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::OpenFileDialog^  ofd;
	private: System::Windows::Forms::Button^  button3;

	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Label^  label1;



			 StringComparer^ stringComparer;


	public:
		MainFrm(void)
		{
			InitializeComponent();
			myError = false;
			therapy = gcnew List<String^>();
			fileName = Environment::GetCommandLineArgs()[0];
			fileName = System::IO::Path::GetFileNameWithoutExtension(fileName);


#ifdef DEBUG
			//tbInformacja->Text = s;
			fileName = "153 (2)";


#endif // DEBUG

			// 2018-11-18 elektros: Find orginal file name
			// Windows adds sufix to the filename of downloded one with identical name
			int spacePos = fileName->IndexOf(" ");
			
			if (spacePos>0) {

				fileName = fileName->Substring(0, spacePos);
			}


			// 2018-11-18 elektros
			if (fileName != "DownloaderCPP") {
				logClear();
				log("$Therapy script number: " + fileName);
			}

			// Read list of available com ports		
			ReadComPortList();

			btnDownload->Enabled = !myError;
			//tmClose->Enabled = myError;
			if (myError)
			{
				//tbInformacja->Text += "\r\nClosing!";
				log("$There is no proper COM port. Connect device and restart script downloader application.");
			}
		}

	static bool ValidateServerCertificate(Object^ sender, X509Certificate^ certificate, X509Chain^ chain, SslPolicyErrors sslPolicyErrors)
	{
		return true;
	}

	private: System::Void ReadComPortList()
	{
		try
		{
			// Get a list of serial port names.
			serialPorts = SerialPort::GetPortNames();
			cbPort->Items->Clear();
			for each(String^ port in serialPorts)
			{
				cbPort->Items->Add(port);
			}

			if (cbPort->Items->Count > 0)
			{
				cbPort->SelectedIndex = 0;
			}
			else
			{
				ShowError("No serial ports!");
				myError = true;
			}
		}
		catch (Win32Exception^ ex)
		{
			MessageBox::Show(this, ex->Message, "Error", MessageBoxButtons::OK);
			ShowError(ex->Message);
			myError = true;
		}
	}

	protected:
		/// <summary>
		/// Clear all resources
		/// </summary>
		~MainFrm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Panel^  pnTop;
	private: System::ComponentModel::IContainer^  components;
	protected:


	private:
		/// <summary>
		/// Wymagana zmienna projektanta.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Wymagana metoda obs³ugi projektanta — nie nale¿y modyfikowaæ 
		/// zawartoœæ tej metody z edytorem kodu.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainFrm::typeid));
			this->pnTop = (gcnew System::Windows::Forms::Panel());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->lbPort = (gcnew System::Windows::Forms::Label());
			this->cbPort = (gcnew System::Windows::Forms::ComboBox());
			this->btnDownload = (gcnew System::Windows::Forms::Button());
			this->tbInformacja = (gcnew System::Windows::Forms::TextBox());
			this->tmClose = (gcnew System::Windows::Forms::Timer(this->components));
			this->btnLIst = (gcnew System::Windows::Forms::Button());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->bankSelector = (gcnew System::Windows::Forms::NumericUpDown());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->ofd = (gcnew System::Windows::Forms::OpenFileDialog());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pnTop->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bankSelector))->BeginInit();
			this->SuspendLayout();
			// 
			// pnTop
			// 
			this->pnTop->Controls->Add(this->pictureBox1);
			this->pnTop->Dock = System::Windows::Forms::DockStyle::Top;
			this->pnTop->Location = System::Drawing::Point(0, 0);
			this->pnTop->Name = L"pnTop";
			this->pnTop->Size = System::Drawing::Size(1429, 86);
			this->pnTop->TabIndex = 1;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->pictureBox1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(1429, 86);
			this->pictureBox1->TabIndex = 5;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &MainFrm::pictureBox1_Click);
			// 
			// lbPort
			// 
			this->lbPort->AutoSize = true;
			this->lbPort->BackColor = System::Drawing::SystemColors::MenuBar;
			this->lbPort->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lbPort->Location = System::Drawing::Point(4, 95);
			this->lbPort->Name = L"lbPort";
			this->lbPort->Size = System::Drawing::Size(29, 13);
			this->lbPort->TabIndex = 3;
			this->lbPort->Text = L"Port:";
			this->lbPort->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// cbPort
			// 
			this->cbPort->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbPort->FormattingEnabled = true;
			this->cbPort->Location = System::Drawing::Point(37, 91);
			this->cbPort->Name = L"cbPort";
			this->cbPort->Size = System::Drawing::Size(121, 21);
			this->cbPort->TabIndex = 2;
			// 
			// btnDownload
			// 
			this->btnDownload->Location = System::Drawing::Point(251, 90);
			this->btnDownload->Name = L"btnDownload";
			this->btnDownload->Size = System::Drawing::Size(75, 23);
			this->btnDownload->TabIndex = 1;
			this->btnDownload->Tag = L"aaa";
			this->btnDownload->Text = L"Download (bank)";
			this->toolTip1->SetToolTip(this->btnDownload, L"Set right COM port and press Download button to save script in the device EEPROM "
				L"memory.");
			this->btnDownload->UseVisualStyleBackColor = true;
			this->btnDownload->Click += gcnew System::EventHandler(this, &MainFrm::btnDownload_Click);
			// 
			// tbInformacja
			// 
			this->tbInformacja->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tbInformacja->Location = System::Drawing::Point(12, 119);
			this->tbInformacja->Multiline = true;
			this->tbInformacja->Name = L"tbInformacja";
			this->tbInformacja->ReadOnly = true;
			this->tbInformacja->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->tbInformacja->Size = System::Drawing::Size(1405, 575);
			this->tbInformacja->TabIndex = 2;
			// 
			// tmClose
			// 
			this->tmClose->Interval = 2000;
			this->tmClose->Tick += gcnew System::EventHandler(this, &MainFrm::tmClose_Tick);
			// 
			// btnLIst
			// 
			this->btnLIst->Location = System::Drawing::Point(332, 90);
			this->btnLIst->Name = L"btnLIst";
			this->btnLIst->Size = System::Drawing::Size(75, 23);
			this->btnLIst->TabIndex = 4;
			this->btnLIst->Text = L"List (bank)";
			this->toolTip1->SetToolTip(this->btnLIst, L"List program script saved in the device EEPROM memory.");
			this->btnLIst->UseVisualStyleBackColor = true;
			this->btnLIst->Click += gcnew System::EventHandler(this, &MainFrm::btnLIst_Click);
			// 
			// toolTip1
			// 
			this->toolTip1->AutoPopDelay = 5000;
			this->toolTip1->InitialDelay = 1000;
			this->toolTip1->ReshowDelay = 500;
			// 
			// bankSelector
			// 
			this->bankSelector->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->bankSelector->Location = System::Drawing::Point(1361, 92);
			this->bankSelector->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 255, 0, 0, 0 });
			this->bankSelector->Name = L"bankSelector";
			this->bankSelector->Size = System::Drawing::Size(56, 20);
			this->bankSelector->TabIndex = 5;
			this->toolTip1->SetToolTip(this->bankSelector, L"Bank (0..255) = Program 1..256");
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(413, 90);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(98, 23);
			this->button1->TabIndex = 7;
			this->button1->Text = L"Index (memlist)";
			this->toolTip1->SetToolTip(this->button1, L"List first two lines of all scripts in external eeprom");
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainFrm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(164, 90);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(80, 23);
			this->button2->TabIndex = 8;
			this->button2->Text = L"From file...";
			this->toolTip1->SetToolTip(this->button2, L"Load theraphy from file.");
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MainFrm::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(517, 90);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(31, 23);
			this->button3->TabIndex = 9;
			this->button3->Text = L"clr";
			this->toolTip1->SetToolTip(this->button3, L"Clear log window");
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MainFrm::button3_Click);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(554, 90);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(106, 23);
			this->button5->TabIndex = 11;
			this->button5->Text = L"Erase (all banks)";
			this->toolTip1->SetToolTip(this->button5, L"Erase all banks");
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MainFrm::button5_Click);
			// 
			// ofd
			// 
			this->ofd->FileName = L"*.*";
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(1320, 94);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(32, 13);
			this->label1->TabIndex = 12;
			this->label1->Text = L"Bank";
			// 
			// MainFrm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1429, 706);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->bankSelector);
			this->Controls->Add(this->lbPort);
			this->Controls->Add(this->tbInformacja);
			this->Controls->Add(this->pnTop);
			this->Controls->Add(this->btnDownload);
			this->Controls->Add(this->btnLIst);
			this->Controls->Add(this->cbPort);
			this->Name = L"MainFrm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Script downloader (zmiany 2018-12-23 Piotr@Reiter.com.pl)";
			this->Shown += gcnew System::EventHandler(this, &MainFrm::MainFrm_Shown);
			this->pnTop->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bankSelector))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	//private: System::Void btnClose_Click(System::Object^  sender, System::EventArgs^  e) {
	//	Close();
	//}
	private: System::Void ShowError(String^ message)
	{
		//MessageBox::Show(this, message, "Error", MessageBoxButtons::OK);
		log("$" +message);
		//tbInformacja->Lines->Add( message );
	}
private: System::Void llBiotronika_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) {
/*	try
	{
		System::Diagnostics::Process::Start("https://biotronics.eu/");
		llBiotronika->LinkVisited = true;
	}
	catch (Exception^ ex)
	{
		ShowError(ex->Message);
	}*/
}
private: System::Void tmClose_Tick(System::Object^  sender, System::EventArgs^  e) {
	Close();
}
	private: System::Void getScript()
	{
		System::Net::Security::RemoteCertificateValidationCallback^ clb = gcnew RemoteCertificateValidationCallback(ValidateServerCertificate);
		System::Net::ServicePointManager::ServerCertificateValidationCallback = clb;

		HttpWebRequest^ request = dynamic_cast<HttpWebRequest^>(WebRequest::Create(adress + fileName));

		request->MaximumAutomaticRedirections = 4;
		request->MaximumResponseHeadersLength = 4;

		// Set credentials to use for this request.
		request->Credentials = CredentialCache::DefaultCredentials;
		HttpWebResponse^ response = dynamic_cast<HttpWebResponse^>(request->GetResponse());

		Stream^ receiveStream = response->GetResponseStream();

		StreamReader^ readStream = gcnew StreamReader(receiveStream, Encoding::UTF8);
		String^ linia;
		while (!readStream->EndOfStream)
		{
			linia = readStream->ReadLine();
			log(linia);
			therapy->Add(linia);
		}
		if (therapy->Count <= 0)
		{
			ShowError("Invalid therapy");
			//tmClose->Enabled = true;
			btnDownload->Enabled = false;
		}

		response->Close();
		readStream->Close();
	}



private: System::Void MainFrm_Shown(System::Object^  sender, System::EventArgs^  e) {
	

	if (!myError)
	{
		getScript();
	};
}

	private: bool OpenPort(String^ portName)
	{
		bool result = false;
		try
		{
			stringComparer = StringComparer::OrdinalIgnoreCase;
			//readThread = gcnew Thread(gcnew ThreadStart(MainFrm::serialRead));
			_serialPort = gcnew SerialPort(portName);
			_serialPort->BaudRate = 9600;
			_serialPort->Parity = System::IO::Ports::Parity::None;
			_serialPort->DataBits = 8;
			//_serialPort->StopBits = System::IO::Ports::StopBits::None;
			_serialPort->Handshake = System::IO::Ports::Handshake::None;
			_serialPort->ReadTimeout = 500;
			_serialPort->WriteTimeout = 500;
			_serialPort->Open();
			Thread::Sleep(300);
			_serialPort->DtrEnable = true;
			Thread::Sleep(250);
			_serialPort->DtrEnable = false;
			//readThread->Start();				
			result = true;
		}
		catch (Exception^ ex)
		{
			MessageBox::Show(this, ex->Message, "Error", MessageBoxButtons::OK);
			ShowError(ex->Message);
			result = false;
		}
		return(result);
	}

	private: void ClosePort()
	{
		_serialPort->Close();
	}

	private: System::Void serialWrite(String^ line)
	{
		_serialPort->WriteLine(line);
		Thread::Sleep(25);
	}
	private: System::Void serialWrite(String^ line,int tm)
	{
		Thread::Sleep(tm);
		serialWrite(line);
		Thread::Sleep(tm);
	}

	private: System::Void readSerial(int time_ms,int sleep) {
		DateTime czas = DateTime::Now;
		String^ linia;
		if(sleep > 0) Thread::Sleep(sleep);
		while ((DateTime::Now - czas).TotalMilliseconds < abs(time_ms))
		{
			try
			{
				linia = _serialPort->ReadLine();
			}
			catch (Exception^) {}

			if (linia != "")
			{
				log(linia);
				linia = "";
				if (time_ms < 0) {
					czas = DateTime::Now;
				}
			}
		}
	}

	private: System::Void readSerial(int time_ms) {
		readSerial(time_ms, 0);
	}

	private: System::Void logClear() {
		tbInformacja->Text = "";
	}

	private: System::Void log(String^ log_line) {
		tbInformacja->AppendText(log_line + "\r\n");
//		tbInformacja->Refresh();
	}

	void SendProgram(int bank, List<String^>^ th)
	{
		//tbInformacja->Text = cbPort->Text;
		if (OpenPort(cbPort->Text))
		{
			log("$" + cbPort->Text + ":Script download");

			String^ linia;

			try
			{
				readSerial(STARTUP_TIME);

				log("bank " + bank);
				serialWrite("bank " + bank);

				serialWrite("mem");
				serialWrite("@");
				//serialWrite("rm");

				readSerial(-150, 200);
				if (th != nullptr) {
					for (int licznik = 0; licznik < th->Count; licznik++)
					{
						linia = th[licznik];
						serialWrite("mem @");
						readSerial(60);
						serialWrite(linia);
						readSerial(10);
						serialWrite("@");
						log(linia);
						readSerial(-150,200);
					}
				}
			}
			catch (Exception^) {

			}
			log("done.");
			ClosePort();
		}
	}

	System::Void btnDownload_Click(System::Object^  sender, System::EventArgs^  e) {
		SendProgram((int)bankSelector->Value, therapy);
	}

private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
	try
	{
		System::Diagnostics::Process::Start("http://biotronics.eu/");
		//llBiotronika->LinkVisited = true;
	}
	catch (Exception^ ex)
	{
		ShowError(ex->Message);
	}
}
private: System::Void btnLIst_Click(System::Object^  sender, System::EventArgs^  e) {

	if (OpenPort(cbPort->Text))
	{
		log("$"+cbPort->Text+":Script list - ls");

		String^ linia;

		try
		{
			readSerial(STARTUP_TIME);

			serialWrite("bank " + bankSelector->Value);

			serialWrite("ls\r\n");

			DateTime czas = DateTime::Now;

			while ((DateTime::Now - czas).TotalMilliseconds < 2000)
			{
				try
				{
					linia = _serialPort->ReadLine();
				}
				catch (Exception^) {}

				if (linia != "")
				{
					log(linia);
					linia = "";
				}
			}



			//serialWrite("@");
			//serialWrite("rm");

			//Thread::Sleep(200);
			/*for (int licznik = 0; licznik < therapy->Count; licznik++)
			{
				linia = therapy[licznik];
				serialWrite("mem @");
				serialWrite(linia);
				serialWrite("@");
				tbInformacja->Text += linia + "\r\n";
				Thread::Sleep(200);
			}*/
		}
		catch (Exception^) {

		}
		ClosePort();
	}

}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	logClear();
	log("Getting index");
	if (OpenPort(cbPort->Text)) {
		readSerial(STARTUP_TIME);
		log("Command: memlist");
		serialWrite("memlist");
		readSerial(5000);
		ClosePort();
		log("done.");
	}
	else
		log("Open port error.");
}

private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	//TODO: choose file
	if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		//load into therapy
		btnDownload->Enabled = false;
		therapy = gcnew List<String^>();
		String^ linia;
		
		System::IO::StreamReader^ sr = gcnew System::IO::StreamReader(ofd->FileName);
		if (sr != nullptr) {
			do {
				linia = sr->ReadLine();
				if (linia != nullptr) {
					log(linia);
					therapy->Add(linia);
				}
			} while (linia != nullptr);
			sr->Close();
			btnDownload->Enabled = therapy->Count > 0;
		}
	}
}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
	logClear();
}
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
	if (OpenPort(cbPort->Text)) {
		try
		{
			readSerial(STARTUP_TIME);
			for (int bank = 0; bank < 256; bank++) {
				log("Erase bank " + bank);
				serialWrite("bank " + bank);
				serialWrite("mem");
				serialWrite("@");
				readSerial(-100,100);
			}
		}
		catch (Exception^) {
		}
		ClosePort();
	}
}
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
}
};
}
