#pragma once
#include <string>

//#define DEBUG

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

	private: System::Windows::Forms::Label^  lbPort;
	private: System::Windows::Forms::ComboBox^  cbPort;
	private: System::Windows::Forms::Button^  btnDownload;

	private: System::Windows::Forms::TextBox^  tbInformacja;

	private: System::Windows::Forms::Timer^  tmClose;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Button^  btnList;

	private: System::Windows::Forms::ToolTip^  toolTip1;
	private: System::Windows::Forms::Button^  btnExe;
	private: System::Windows::Forms::Button^  btnRm;


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
			fileName = "162 (2)";


#endif // DEBUG

			// 2018-11-18 elektros: Find orginal file name
			// Windows adds sufix to the filename of downloded one with identical name
			int spacePos = fileName->IndexOf(" ");
			
			if (spacePos>0) {

				fileName = fileName->Substring(0, spacePos);
			}


			// 2018-11-18 elektros
			if (fileName != "DownloaderCPP") {
				tbInformacja->Text = "$Therapy script number: " + fileName;
				tbInformacja->Text += "\r\n";
			}

			// Read list of available com ports		
			ReadComPortList();

			btnDownload->Enabled = !myError;
			//tmClose->Enabled = myError;
			if (myError)
			{
				//tbInformacja->Text += "\r\nClosing!";
				tbInformacja->Text += "\r\n";
				tbInformacja->Text += "$There is no proper COM port. Connect device and restart script downloader application.";
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
			this->btnList = (gcnew System::Windows::Forms::Button());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->btnExe = (gcnew System::Windows::Forms::Button());
			this->btnRm = (gcnew System::Windows::Forms::Button());
			this->pnTop->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pnTop
			// 
			this->pnTop->Controls->Add(this->pictureBox1);
			this->pnTop->Dock = System::Windows::Forms::DockStyle::Top;
			this->pnTop->Location = System::Drawing::Point(0, 0);
			this->pnTop->Name = L"pnTop";
			this->pnTop->Size = System::Drawing::Size(698, 86);
			this->pnTop->TabIndex = 1;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(698, 86);
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
			this->btnDownload->Location = System::Drawing::Point(166, 90);
			this->btnDownload->Name = L"btnDownload";
			this->btnDownload->Size = System::Drawing::Size(75, 23);
			this->btnDownload->TabIndex = 1;
			this->btnDownload->Tag = L"aaa";
			this->btnDownload->Text = L"Download";
			this->toolTip1->SetToolTip(this->btnDownload, L"Save script into the device memory.memory.");
			this->btnDownload->UseVisualStyleBackColor = true;
			this->btnDownload->Click += gcnew System::EventHandler(this, &MainFrm::btnDownload_Click);
			// 
			// tbInformacja
			// 
			this->tbInformacja->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->tbInformacja->Location = System::Drawing::Point(0, 118);
			this->tbInformacja->Multiline = true;
			this->tbInformacja->Name = L"tbInformacja";
			this->tbInformacja->ReadOnly = true;
			this->tbInformacja->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->tbInformacja->Size = System::Drawing::Size(698, 213);
			this->tbInformacja->TabIndex = 2;
			this->tbInformacja->WordWrap = false;
			this->tbInformacja->TextChanged += gcnew System::EventHandler(this, &MainFrm::tbInformacja_TextChanged);
			// 
			// tmClose
			// 
			this->tmClose->Interval = 2000;
			this->tmClose->Tick += gcnew System::EventHandler(this, &MainFrm::tmClose_Tick);
			// 
			// btnList
			// 
			this->btnList->Location = System::Drawing::Point(249, 90);
			this->btnList->Name = L"btnList";
			this->btnList->Size = System::Drawing::Size(37, 23);
			this->btnList->TabIndex = 4;
			this->btnList->Text = L"ls";
			this->toolTip1->SetToolTip(this->btnList, L"List program script saved in the device memory.");
			this->btnList->UseVisualStyleBackColor = true;
			this->btnList->Click += gcnew System::EventHandler(this, &MainFrm::btnLIst_Click);
			// 
			// toolTip1
			// 
			this->toolTip1->AutoPopDelay = 5000;
			this->toolTip1->InitialDelay = 1000;
			this->toolTip1->ReshowDelay = 500;
			// 
			// btnExe
			// 
			this->btnExe->Location = System::Drawing::Point(294, 90);
			this->btnExe->Name = L"btnExe";
			this->btnExe->Size = System::Drawing::Size(37, 23);
			this->btnExe->TabIndex = 5;
			this->btnExe->Text = L"exe";
			this->toolTip1->SetToolTip(this->btnExe, L"Execute user script from device memory.");
			this->btnExe->UseVisualStyleBackColor = true;
			this->btnExe->Click += gcnew System::EventHandler(this, &MainFrm::btnExe_Click);
			// 
			// btnRm
			// 
			this->btnRm->Location = System::Drawing::Point(338, 90);
			this->btnRm->Name = L"btnRm";
			this->btnRm->Size = System::Drawing::Size(37, 23);
			this->btnRm->TabIndex = 6;
			this->btnRm->Text = L"rm";
			this->toolTip1->SetToolTip(this->btnRm, L"Remove script from device memory.");
			this->btnRm->UseVisualStyleBackColor = true;
			this->btnRm->Click += gcnew System::EventHandler(this, &MainFrm::btnRm_Click);
			// 
			// MainFrm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(698, 331);
			this->Controls->Add(this->btnRm);
			this->Controls->Add(this->btnExe);
			this->Controls->Add(this->lbPort);
			this->Controls->Add(this->tbInformacja);
			this->Controls->Add(this->pnTop);
			this->Controls->Add(this->btnDownload);
			this->Controls->Add(this->btnList);
			this->Controls->Add(this->cbPort);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"MainFrm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Script downloader";
			this->Shown += gcnew System::EventHandler(this, &MainFrm::MainFrm_Shown);
			this->pnTop->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
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
		tbInformacja->Text += "$" +message + "\r\n";
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
			tbInformacja->Text += linia + "\r\n";
			therapy->Add(linia);
		}
		if (therapy->Count <= 0)
		{
			ShowError("Invalid therapy");
			//tmClose->Enabled = true;
			btnDownload->Enabled = false;
			
			
			//toolTip1->ShowAlways = true;

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
			Thread::Sleep(200);
			_serialPort->DtrEnable = true;
			Thread::Sleep(50);
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
	}


private: System::Void btnDownload_Click(System::Object^  sender, System::EventArgs^  e) {
	//tbInformacja->Text = cbPort->Text;
	if (OpenPort(cbPort->Text))
	{
		tbInformacja->Text = "$"+ cbPort->Text+":Script download";

		String^ linia;

		try
		{
			DateTime czas = DateTime::Now;

			while ((DateTime::Now - czas).TotalMilliseconds<2000)
			{
				try
				{
					linia = _serialPort->ReadLine();
				}
				catch (Exception^) {}

				if (linia != "")
				{
					tbInformacja->Text += linia + "\r\n";
					linia = "";
				}
			}
			Thread::Sleep(1500);
			serialWrite("mem\n");
			Thread::Sleep(15);
			serialWrite("@");
			//serialWrite("rm");

			Thread::Sleep(150);
			for (int licznik = 0; licznik < therapy->Count; licznik++)
			{
				linia = therapy[licznik];
				serialWrite("mem @");
				Thread::Sleep(15);
				serialWrite(linia);
				Thread::Sleep(15);
				serialWrite("@");
				tbInformacja->Text += linia + "\r\n";
				tbInformacja->Refresh();
				Thread::Sleep(150);
			}
		}
		catch (Exception^) {

		}
		ClosePort();
	}
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
	//tbInformacja->Text = cbPort->Text;
	if (OpenPort(cbPort->Text))
	{
		tbInformacja->Text = "$"+cbPort->Text+">ls";

		String^ linia;

		try
		{
			DateTime czas = DateTime::Now;

			
			while ((DateTime::Now - czas).TotalMilliseconds < 1500)
			{
				try
				{
					linia = _serialPort->ReadLine();
				}
				catch (Exception^) {}

				if (linia != "")
				{
					tbInformacja->Text += linia + "\r\n";
					linia = "";
				}
			}
			Thread::Sleep(1500);


			serialWrite("ls\r\n");

			czas = DateTime::Now;

			while ((DateTime::Now - czas).TotalMilliseconds < 2000)
			{
				try
				{
					linia = _serialPort->ReadLine();
				}
				catch (Exception^) {}

				if (linia != "")
				{
					tbInformacja->Text += linia + "\r\n";
					tbInformacja->Refresh();
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
private: System::Void tbInformacja_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void btnExe_Click(System::Object^  sender, System::EventArgs^  e) {
	if (OpenPort(cbPort->Text))
	{
		tbInformacja->Text = "$" + cbPort->Text + ">exe";

		String^ linia;

		try
		{
			DateTime czas = DateTime::Now;


			while ((DateTime::Now - czas).TotalMilliseconds < 1500)
			{
				try
				{
					linia = _serialPort->ReadLine();
				}
				catch (Exception^) {}

				if (linia != "")
				{
					tbInformacja->Text += linia + "\r\n";
					linia = "";
				}
			}
			Thread::Sleep(1500);


			serialWrite("exe\n");

			czas = DateTime::Now;

			while ((DateTime::Now - czas).TotalMilliseconds < 2000)
			{
				try
				{
					linia = _serialPort->ReadLine();
				}
				catch (Exception^) {}

				if (linia != "")
				{
					tbInformacja->Text += linia + "\r\n";
					tbInformacja->Refresh();
					linia = "";
				}
			}



		}
		catch (Exception^) {

		}
		ClosePort();
	}

}
private: System::Void btnRm_Click(System::Object^  sender, System::EventArgs^  e) {
	if (OpenPort(cbPort->Text))
	{
		tbInformacja->Text = "$" + cbPort->Text + ">exe";

		String^ linia;

		try
		{
			DateTime czas = DateTime::Now;


			while ((DateTime::Now - czas).TotalMilliseconds < 1500)
			{
				try
				{
					linia = _serialPort->ReadLine();
				}
				catch (Exception^) {}

				if (linia != "")
				{
					tbInformacja->Text += linia + "\r\n";
					linia = "";
				}
			}
			Thread::Sleep(1500);


			serialWrite("rm\n");

			czas = DateTime::Now;

			while ((DateTime::Now - czas).TotalMilliseconds < 2000)
			{
				try
				{
					linia = _serialPort->ReadLine();
				}
				catch (Exception^) {}

				if (linia != "")
				{
					tbInformacja->Text += linia + "\r\n";
					tbInformacja->Refresh();
					linia = "";
				}
			}



		}
		catch (Exception^) {

		}
		ClosePort();
	}
}
};
}
