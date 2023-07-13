unit frmPrincipal;

interface

uses
  System.SysUtils, System.Types, System.UITypes, System.Classes, System.Variants,
  FMX.Types, FMX.Controls, FMX.Forms, FMX.Graphics, FMX.Dialogs, FMX.TabControl,
  FMX.Objects, FMX.Controls.Presentation, FMX.StdCtrls, FMX.Layouts,
  FMX.ScrollBox, FMX.Memo, System.Actions, FMX.ActnList, TMS.MQTT.Global,
  TMS.MQTT.Client, UNetworkState;

type
  TfrmMain = class(TForm)
    TabControlAquabox: TTabControl;
    tabPrincipal: TTabItem;
    tabCaixa: TTabItem;
    tabResumo: TTabItem;
    tabTelefone: TTabItem;
    tabAjuda: TTabItem;
    Rectangle1: TRectangle;
    Layout1: TLayout;
    Image1: TImage;
    Layout2: TLayout;
    Label1: TLabel;
    Layout3: TLayout;
    Label2: TLabel;
    Layout4: TLayout;
    Label3: TLabel;
    Layout5: TLayout;
    Layout6: TLayout;
    Layout7: TLayout;
    Label4: TLabel;
    Rectangle2: TRectangle;
    Layout8: TLayout;
    Rectangle3: TRectangle;
    Image2: TImage;
    Layout9: TLayout;
    Rectangle4: TRectangle;
    Layout10: TLayout;
    Layout11: TLayout;
    Layout12: TLayout;
    Layout13: TLayout;
    Layout14: TLayout;
    Layout15: TLayout;
    Layout16: TLayout;
    Layout17: TLayout;
    Rectangle5: TRectangle;
    Rectangle6: TRectangle;
    Rectangle7: TRectangle;
    Rectangle8: TRectangle;
    Rectangle9: TRectangle;
    Rectangle10: TRectangle;
    Rectangle11: TRectangle;
    Rectangle12: TRectangle;
    lblNome: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    lblStatus: TLabel;
    lblSensorNivelBaixo: TLabel;
    lblSensorNivelAlto: TLabel;
    lblFalha: TLabel;
    lblBotaoOnOff: TLabel;
    lblBotaoModo: TLabel;
    Rectangle13: TRectangle;
    Layout18: TLayout;
    Rectangle14: TRectangle;
    Image3: TImage;
    Layout19: TLayout;
    Rectangle15: TRectangle;
    Layout20: TLayout;
    Rectangle16: TRectangle;
    Label18: TLabel;
    Layout21: TLayout;
    Rectangle17: TRectangle;
    Label19: TLabel;
    lblResumoVStatus: TLabel;
    Layout22: TLayout;
    Rectangle18: TRectangle;
    Label21: TLabel;
    lblResumoVFalha: TLabel;
    Layout23: TLayout;
    Rectangle19: TRectangle;
    Label23: TLabel;
    lblResumoCStatus: TLabel;
    Layout24: TLayout;
    Rectangle20: TRectangle;
    Label25: TLabel;
    lblResumoCFalha: TLabel;
    Layout25: TLayout;
    Rectangle21: TRectangle;
    Label27: TLabel;
    lblResumoHStatus: TLabel;
    Layout26: TLayout;
    Rectangle22: TRectangle;
    Label29: TLabel;
    lblResumoHFalha: TLabel;
    Layout27: TLayout;
    Rectangle23: TRectangle;
    Rectangle24: TRectangle;
    Layout28: TLayout;
    Rectangle25: TRectangle;
    Image4: TImage;
    Layout29: TLayout;
    Rectangle26: TRectangle;
    Layout30: TLayout;
    Rectangle27: TRectangle;
    Label31: TLabel;
    Layout31: TLayout;
    Rectangle28: TRectangle;
    Label32: TLabel;
    Label33: TLabel;
    Layout32: TLayout;
    Rectangle29: TRectangle;
    Label34: TLabel;
    Label35: TLabel;
    Layout33: TLayout;
    Rectangle30: TRectangle;
    Label36: TLabel;
    Label37: TLabel;
    Layout34: TLayout;
    Rectangle31: TRectangle;
    Label38: TLabel;
    Label39: TLabel;
    Layout35: TLayout;
    Rectangle32: TRectangle;
    Layout37: TLayout;
    Rectangle34: TRectangle;
    Label40: TLabel;
    Label41: TLabel;
    Label42: TLabel;
    Rectangle33: TRectangle;
    Layout36: TLayout;
    Rectangle35: TRectangle;
    Image5: TImage;
    Layout38: TLayout;
    Rectangle36: TRectangle;
    Layout39: TLayout;
    Rectangle37: TRectangle;
    Label43: TLabel;
    Layout40: TLayout;
    Rectangle38: TRectangle;
    Label45: TLabel;
    Layout41: TLayout;
    Rectangle39: TRectangle;
    Label47: TLabel;
    Layout42: TLayout;
    Rectangle40: TRectangle;
    Label49: TLabel;
    Layout43: TLayout;
    Rectangle41: TRectangle;
    Label51: TLabel;
    Layout44: TLayout;
    Rectangle42: TRectangle;
    Label52: TLabel;
    Label53: TLabel;
    Label54: TLabel;
    Layout45: TLayout;
    Rectangle43: TRectangle;
    Circle18: TCircle;
    Layout46: TLayout;
    Circle1: TCircle;
    btnValderi: TSpeedButton;
    Image6: TImage;
    Layout47: TLayout;
    Circle2: TCircle;
    btnHenrique: TSpeedButton;
    Image7: TImage;
    Layout48: TLayout;
    Circle3: TCircle;
    btnCristiano: TSpeedButton;
    Image8: TImage;
    Layout49: TLayout;
    Circle4: TCircle;
    btnTelefoneMain: TSpeedButton;
    Image9: TImage;
    Layout50: TLayout;
    Circle5: TCircle;
    btnAjudaMain: TSpeedButton;
    Image10: TImage;
    Layout51: TLayout;
    Circle6: TCircle;
    btnResumo: TSpeedButton;
    Image11: TImage;
    Layout52: TLayout;
    Circle7: TCircle;
    btnMenuCaixa: TSpeedButton;
    Image12: TImage;
    Layout53: TLayout;
    Circle8: TCircle;
    btnAvancar: TSpeedButton;
    Image13: TImage;
    Layout54: TLayout;
    Circle9: TCircle;
    btnTelefoneCaixa: TSpeedButton;
    Image14: TImage;
    Layout55: TLayout;
    Circle10: TCircle;
    btnAjudaCaixa: TSpeedButton;
    Image15: TImage;
    Layout56: TLayout;
    Circle11: TCircle;
    btnMenuResumo: TSpeedButton;
    Image16: TImage;
    Layout57: TLayout;
    Circle13: TCircle;
    btnTelefoneResumo: TSpeedButton;
    Image17: TImage;
    Layout58: TLayout;
    Circle14: TCircle;
    btnAjudaResumo: TSpeedButton;
    Image18: TImage;
    Layout59: TLayout;
    Circle12: TCircle;
    btnMenuTelefone: TSpeedButton;
    Image19: TImage;
    Layout60: TLayout;
    Circle22: TCircle;
    btnAjudaTelefone: TSpeedButton;
    Image20: TImage;
    Layout61: TLayout;
    Circle15: TCircle;
    btnMenuAjuda: TSpeedButton;
    Image21: TImage;
    Layout62: TLayout;
    Circle16: TCircle;
    btnTelefoneAjuda: TSpeedButton;
    Image22: TImage;
    Image23: TImage;
    Circle17: TCircle;
    Image24: TImage;
    Circle19: TCircle;
    Image25: TImage;
    Circle20: TCircle;
    Image26: TImage;
    ActionList1: TActionList;
    actPrincipal: TChangeTabAction;
    actCaixa: TChangeTabAction;
    actResumo: TChangeTabAction;
    actTelefone: TChangeTabAction;
    actAjuda: TChangeTabAction;
    Layout63: TLayout;
    Layout64: TLayout;
    MQTTClient: TTMSMQTTClient;
    Layout65: TLayout;
    imgCaixaOff: TImage;
    imgCaixaOn: TImage;
    Layout66: TLayout;
    imgResumoOff: TImage;
    imgResumoOn: TImage;
    imgCaixaBroker: TImage;
    imgResumoBroker: TImage;
    Timer: TTimer;
    Layout67: TLayout;
    lblHora: TLabel;
    layout: TLayout;
    lblHoraResumo: TLabel;
    procedure btnValderiClick(Sender: TObject);
    procedure btnCristianoClick(Sender: TObject);
    procedure btnHenriqueClick(Sender: TObject);
    procedure btnTelefoneMainClick(Sender: TObject);
    procedure btnResumoClick(Sender: TObject);
    procedure btnAjudaMainClick(Sender: TObject);
    procedure btnMenuCaixaClick(Sender: TObject);
    procedure btnTelefoneCaixaClick(Sender: TObject);
    procedure btnAjudaCaixaClick(Sender: TObject);
    procedure btnMenuResumoClick(Sender: TObject);
    procedure btnTelefoneResumoClick(Sender: TObject);
    procedure btnAjudaResumoClick(Sender: TObject);
    procedure btnMenuTelefoneClick(Sender: TObject);
    procedure btnAjudaTelefoneClick(Sender: TObject);
    procedure btnMenuAjudaClick(Sender: TObject);
    procedure btnTelefoneAjudaClick(Sender: TObject);

    procedure FormCreate(Sender: TObject);
    procedure TMSMQTTClient1ConnectedStatusChanged(ASender: TObject;
              const AConnected: Boolean; AStatus: TTMSMQTTConnectionStatus);
    Procedure PublishReceived(ASender: TObject; APacketID: Word;
              ATopic: string; APayload: TBytes);
    procedure Atualizar();
    procedure btnAvancarClick(Sender: TObject);
    procedure Conectar();
    procedure TimerTimer(Sender: TObject);
    procedure DadosValderi();
    procedure DadosCristiano();
    procedure DadosHenrique();
    procedure DadosResumo();
    procedure FormActivate(Sender: TObject);

  private
    FNetworkState: TNetworkState;
  protected
    procedure DoOnChange(Sender: TObject; Value: TNetworkStateValue);
  public
    { Public declarations }
  end;

var
  frmMain: TfrmMain;
  resposta: string;
  pagina: integer;
  conectado: integer;
  TextoPadrao: string;
  contador: integer;
  temp: integer;
  IMEI: String;


implementation

{$IFDEF ANDROID}
uses
  Androidapi.JNI.GraphicsContentViewText, AndroidApi.Helpers,
	AndroidApi.JNI.Telephony, AndroidApi.JNI.Provider, AndroidApi.JNIBridge,
	AndroidApi.JNI.JavaTypes, AndroidApi.JNI.Os, AndroidApi.JNI.App;
{$ENDIF}

{$R *.fmx}

procedure TfrmMain.FormCreate(Sender: TObject);
var //Variaveis para captura do IMEI
  obj: JObject;
	tm: JTelephonyManager;

begin

  self.FNetworkState := TNetworkState.Factory(self, DoOnChange);

  MQTTClient := TTMSMQTTClient.Create(Self);
  MQTTClient.OnPublishReceived := PublishReceived;

  //Capturar IMEI
  IMEI:= '';
	  obj:= TAndroidHelper.Activity.getSystemService
		      (TJContext.JavaClass.TELEPHONY_SERVICE);
	  if (obj <> nil) then
	    begin
		    tm:= TJTelephonyManager.Wrap((obj as ILocalObject).GetObjectID);
		    if (tm <> nil) then
			    IMEI:= JStringToString(tm.getDeviceId);
	    end;
		if (IMEI = '') then
			IMEI := JStringToString(TJSettings_Secure.JavaClass.getString
				      (TAndroidHelper.Activity.getContentResolver,
				      TJSettings_Secure.JavaClass.ANDROID_ID));

end;

procedure TfrmMain.FormActivate(Sender: TObject);
begin
  if (self.FNetworkState.CurrentValue = nsConnectedWifi) or (self.FNetworkState.CurrentValue = nsConnectedMobileData ) then
    //Conectado
    begin

      conectado:= 1;
      Conectar();

      self.imgCaixaOn.Visible:= true;
      self.imgCaixaBroker.Visible:= false;
      self.imgResumoOn.Visible:= true;
      self.imgResumoBroker.Visible:= false;
      self.imgCaixaOff.Visible:= false;
      self.imgResumoOff.Visible:= false;

    end
  else if self.FNetworkState.CurrentValue = nsDisconnected then
    //Não Conectado
    begin

    conectado:= 0;

    self.imgCaixaOn.Visible:= false;
    self.imgCaixaBroker.Visible:= false;
    self.imgCaixaOff.Visible:= true;
    self.imgResumoOn.Visible:= false;
    self.imgResumoBroker.Visible:= false;
    self.imgResumoOff.Visible:= true;
    end
  else
    //Conexão desconhecida
    begin

    conectado:= 0;
    self.imgCaixaOn.Visible:= false;
    self.imgCaixaBroker.Visible:= false;
    self.imgCaixaOff.Visible:= true;
    self.imgResumoOn.Visible:= false;
    self.imgResumoBroker.Visible:= false;
    self.imgResumoOff.Visible:= true;
    end
end;

procedure TfrmMain.TimerTimer(Sender: TObject);
begin
  Atualizar();
end;

procedure TfrmMain.Conectar();
begin
  MQTTClient.ClientID:= IMEI;
  MQTTClient.BrokerHostName := 'm11.cloudmqtt.com';
  MQTTClient.BrokerPort :=  10860;
  MQTTClient.Credentials.Username := 'hpredaum';
  MQTTClient.Credentials.Password := 'mZMw2G6XpTVE';
  MQTTClient.KeepAliveSettings.KeepConnectionAlive := true; //Mantém conexão viva
  //self.MQTTClient.KeepAliveSettings.KeepAliveInterval := 60;
  MQTTClient.KeepAliveSettings.AutoReconnect := true;  //autoconecta-se
  MQTTClient.KeepAliveSettings.AutoReconnectInterval := 10; //se cair por mais de 10s
  MQTTClient.OnConnectedStatusChanged := TMSMQTTClient1ConnectedStatusChanged;
  MQTTClient.Connect;
end;

Procedure TfrmMain.TMSMQTTClient1ConnectedStatusChanged(Asender: TObject; const
          AConnected: Boolean; AStatus: TTMSMQTTConnectionStatus);
  begin
    if (AConnected) then
  begin
// The client is now connected and you can now start interacting with the broker.
  ShowMessage('Estamos conectado!');
  MQTTClient.Subscribe('Aquabox');

  end
else
  begin
// The client is NOT connected and any interaction with the broker will result in
//an exception.
    {
    case AStatus of
      csConnectionRejected_InvalidProtocolVersion,
      csConnectionRejected_InvalidIdentifier,
      csConnectionRejected_ServerUnavailable,
      csConnectionRejected_InvalidCredentials,
      csConnectionRejected_ClientNotAuthorized:;
 // the connection is rejected by broker
      csConnectionLost:;
 // the connection with the broker is lost
      csConnecting:;
 // The client is trying to connect to the broker
      csReconnecting:;
 // The client is trying to reconnect to the broker
    end;
    }
  end;
end;

Procedure TfrmMain.PublishReceived(ASender: TObject; APacketID: Word;
ATopic: string; APayload: TBytes);
begin
  //ShowMessage('Mensagem recebida no tópico: ' + ATopic + sLineBreak +
  //TEncoding.UTF8.GetString(APayload));

  resposta:= TEncoding.UTF8.GetString(APayload);
  lblHora.Text:= DateTimeToStr(Now);
  lblHoraResumo.Text:= DateTimeToStr(Now);

end;

procedure TfrmMain.DoOnChange(Sender: TObject; Value: TNetworkStateValue);
begin

  if (Value = nsConnectedWifi) or (Value = nsConnectedMobileData) then
  //Se conectado
  begin
    conectado:= 1;
    Conectar();

    self.imgCaixaOn.Visible:= true;
    self.imgCaixaBroker.Visible:= false;
    self.imgResumoOn.Visible:= true;
    self.imgResumoBroker.Visible:= false;
    self.imgCaixaOff.Visible:= false;
    self.imgResumoOff.Visible:= false;
  end

  else if self.FNetworkState.CurrentValue = nsDisconnected then
  //Não conectado
    begin
    conectado:= 0;
    self.imgCaixaOn.Visible:= false;
    self.imgCaixaBroker.Visible:= false;
    self.imgCaixaOff.Visible:= true;
    self.imgResumoOn.Visible:= false;
    self.imgResumoBroker.Visible:= false;
    self.imgResumoOff.Visible:= true;
    end
  else
  //Desconhecido
    begin
    conectado:= 0;
    self.imgCaixaOn.Visible:= false;
    self.imgCaixaBroker.Visible:= false;
    self.imgCaixaOff.Visible:= true;
    self.imgResumoOn.Visible:= false;
    self.imgResumoBroker.Visible:= false;
    self.imgResumoOff.Visible:= true;
    end
end;

//Trata dados Valderi
procedure TfrmMain.DadosValderi(); //Tratar o payload convertendo em informação válida

begin
  contador:= 1;
  temp:= StrToInt(Copy(resposta, contador, 1));  //Nome

  if(temp = 1) then
    begin
      lblNome.Text:= 'VALDERI';
    end
  else
    begin
      lblNome.Text:= 'Desconhecido';
    end;

  contador:= contador + 1;
  temp:= StrToInt(Copy(resposta, contador, 1));  //Status Caixa
  case temp of
  0:
    begin
      lblStatus.Text:= 'Cheia';
    end;
  1:
    begin
      lblStatus.Text:= 'Vazia';
    end;
  2:
    begin
      lblStatus.Text:= 'Normal';
    end;
  3:
    begin
      lblStatus.Text:= 'Enchendo';
    end;
  else
    begin
      lblStatus.Text:= 'Desconhecido';
    end;
  end;

  contador:= contador + 1;
  lblSensorNivelBaixo.Text:= Copy(resposta, contador, 2) + ':' +  //Tempo sensor de nivel baixo
                             Copy(resposta, contador+2, 2) + ':' +
                             Copy(resposta, contador+4, 2);

  contador:= contador + 6;
  lblSensorNivelAlto.Text:= Copy(resposta, Contador, 2)  + ':' + //Tempo sensor de nivel alto
                       Copy(resposta, contador+2, 2) + ':' +
                       Copy(resposta, contador+4, 2);

  contador:= contador + 6;
  temp:= StrToInt(Copy(resposta, contador, 1)); //Falha
  case temp of
  0:
    begin
      lblFalha.Text:= 'Normal';
    end;
  1:
    begin
      lblFalha.Text:= 'Sensores';
    end;
  2:
    begin
      lblFalha.Text:= 'Vazão';
    end;
  else
    begin
      lblFalha.Text:= 'Desconhecido';
    end;
  end;

  contador:= contador + 1;
  temp:= StrToInt(Copy(resposta, contador,1)); //Status botão On/Off
  case temp of
  0:
    begin
      lblBotaoOnOff.Text:= 'Desabilitado';
    end;
  1:
    begin
      lblBotaoOnOff.Text:= 'Habilitado';
    end;
  else
    begin
      lblBotaoOnOff.Text:= 'Desconhecido';
    end;
  end;

  contador:= 49;

  temp:= StrToInt(Copy(resposta, contador,1)); //Status botão Modo
    case temp of
  0:
    begin
      lblBotaoModo.Text:= 'Desabilitado';
    end;
  1:
    begin
      lblBotaoModo.Text:= 'Habilitado';
    end;
  else
    begin
      lblBotaoModo.Text:= 'Desconhecido';
    end;
  end;

end;

//Trata dados Cristiano
procedure TfrmMain.DadosCristiano(); //Tratar o payload convertendo em informação válida

begin
  contador:= 17;
  temp:= StrToInt(Copy(resposta, contador, 1));  //Nome
  if(temp = 2) then
    begin
      lblNome.Text:= 'CRISTIANO';
    end
  else
    begin
      lblNome.Text:= 'Desconhecido';
    end;

  contador:= contador + 1;
  temp:= StrToInt(Copy(resposta, contador, 1));  //Status Caixa
  case temp of
  0:
    begin
      lblStatus.Text:= 'Cheia';
    end;
  1:
    begin
      lblStatus.Text:= 'Vazia';
    end;
  2:
    begin
      lblStatus.Text:= 'Normal';
    end;
  3:
    begin
      lblStatus.Text:= 'Enchendo';
    end;
  else
    begin
      lblStatus.Text:= 'Desconhecido';
    end;
  end;

  contador:= contador + 1;
  lblSensorNivelBaixo.Text:= Copy(resposta, contador, 2) + ':' +  //Tempo sensor de nivel baixo
                             Copy(resposta, contador+2, 2) + ':' +
                             Copy(resposta, contador+4, 2);

  contador:= contador + 6;
  lblSensorNivelAlto.Text:= Copy(resposta, Contador, 2)  + ':' + //Tempo sensor de nivel alto
                       Copy(resposta, contador+2, 2) + ':' +
                       Copy(resposta, contador+4, 2);

  contador:= contador + 6;
  temp:= StrToInt(Copy(resposta, contador, 1)); //Falha
  case temp of
  0:
    begin
      lblFalha.Text:= 'Normal';
    end;
  1:
    begin
      lblFalha.Text:= 'Sensores';
    end;
  2:
    begin
      lblFalha.Text:= 'Vazão';
    end;
  else
    begin
      lblFalha.Text:= 'Desconhecido';
    end;
  end;

  contador:= contador + 1;
  temp:= StrToInt(Copy(resposta, contador,1)); //Status botão On/Off
  case temp of
  0:
    begin
      lblBotaoOnOff.Text:= 'Desabilitado';
    end;
  1:
    begin
      lblBotaoOnOff.Text:= 'Habilitado';
    end;
  else
    begin
      lblBotaoOnOff.Text:= 'Desconhecido';
    end;
  end;

  contador:= 49;

  temp:= StrToInt(Copy(resposta, contador,1)); //Status botão Modo
    case temp of
  0:
    begin
      lblBotaoModo.Text:= 'Desabilitado';
    end;
  1:
    begin
      lblBotaoModo.Text:= 'Habilitado';
    end;
  else
    begin
      lblBotaoModo.Text:= 'Desconhecido';
    end;
  end;

end;

//Trata dados Henrique
procedure TfrmMain.DadosHenrique(); //Tratar o payload convertendo em informação válida

begin
  contador:= 33;
  temp:= StrToInt(Copy(resposta, contador, 1));  //Nome
  if(temp = 3) then
    begin
      lblNome.Text:= 'HENRIQUE';
    end
  else
    begin
      lblNome.Text:= 'Desconhecido';
    end;

  contador:= contador + 1;
  temp:= StrToInt(Copy(resposta, contador, 1));  //Status Caixa
  case temp of
  0:
    begin
      lblStatus.Text:= 'Cheia';
    end;
  1:
    begin
      lblStatus.Text:= 'Vazia';
    end;
  2:
    begin
      lblStatus.Text:= 'Normal';
    end;
  3:
    begin
      lblStatus.Text:= 'Enchendo';
    end;
  else
    begin
      lblStatus.Text:= 'Desconhecido';
    end;
  end;

  contador:= contador + 1;
  lblSensorNivelBaixo.Text:= Copy(resposta, contador, 2) + ':' +  //Tempo sensor de nivel baixo
                             Copy(resposta, contador+2, 2) + ':' +
                             Copy(resposta, contador+4, 2);

  contador:= contador + 6;
  lblSensorNivelAlto.Text:= Copy(resposta, Contador, 2)  + ':' + //Tempo sensor de nivel alto
                       Copy(resposta, contador+2, 2) + ':' +
                       Copy(resposta, contador+4, 2);

  contador:= contador + 6;
  temp:= StrToInt(Copy(resposta, contador, 1)); //Falha
  case temp of
  0:
    begin
      lblFalha.Text:= 'Normal';
    end;
  1:
    begin
      lblFalha.Text:= 'Sensores';
    end;
  2:
    begin
      lblFalha.Text:= 'Vazão';
    end;
  else
    begin
      lblFalha.Text:= 'Desconhecido';
    end;
  end;

  contador:= contador + 1;
  temp:= StrToInt(Copy(resposta, contador,1)); //Status botão On/Off
  case temp of
  0:
    begin
      lblBotaoOnOff.Text:= 'Desabilitado';
    end;
  1:
    begin
      lblBotaoOnOff.Text:= 'Habilitado';
    end;
  else
    begin
      lblBotaoOnOff.Text:= 'Desconhecido';
    end;
  end;

  contador:= 49;

  temp:= StrToInt(Copy(resposta, contador,1)); //Status botão Modo
    case temp of
  0:
    begin
      lblBotaoModo.Text:= 'Desabilitado';
    end;
  1:
    begin
      lblBotaoModo.Text:= 'Habilitado';
    end;
  else
    begin
      lblBotaoModo.Text:= 'Desconhecido';
    end;
  end;

end;

//Dados Resumo
 procedure TfrmMain.DadosResumo(); //Tratar o payload convertendo em informação válida

  //Valderi Resumo
begin
  contador:= 2;
  temp:= StrToInt(Copy(resposta, contador, 1));  //Status Caixa
  case temp of
  0:
    begin
      lblResumoVStatus.Text:= 'Cheia';
    end;
  1:
    begin
      lblResumoVStatus.Text:= 'Vazia';
    end;
  2:
    begin
      lblResumoVStatus.Text:= 'Normal';
    end;
  3:
    begin
      lblResumoVStatus.Text:= 'Enchendo';
    end;
  else
    begin
      lblResumoVStatus.Text:= 'Desconhecido';
    end;
  end;

  contador:= 15;
  temp:= StrToInt(Copy(resposta, contador, 1)); //Falha
  case temp of
  0:
    begin
      lblResumoVFalha.Text:= 'Normal';
    end;
  1:
    begin
      lblResumoVFalha.Text:= 'Sensores';
    end;
  2:
    begin
      lblResumoVFalha.Text:= 'Vazão';
    end;
  else
    begin
      lblResumoVFalha.Text:= 'Desconhecido';
    end;
  end;

//Cristiano Resumo
  contador:= 18;
  temp:= StrToInt(Copy(resposta, contador, 1));  //Status Caixa
  case temp of
  0:
    begin
      lblResumoCStatus.Text:= 'Cheia';
    end;
  1:
    begin
      lblResumoCStatus.Text:= 'Vazia';
    end;
  2:
    begin
      lblResumoCStatus.Text:= 'Normal';
    end;
  3:
    begin
      lblResumoCStatus.Text:= 'Enchendo';
    end;
  else
    begin
      lblResumoCStatus.Text:= 'Desconhecido';
    end;
  end;

  contador:= 31;
  temp:= StrToInt(Copy(resposta, contador, 1)); //Falha
  case temp of
  0:
    begin
      lblResumoCFalha.Text:= 'Normal';
    end;
  1:
    begin
      lblResumoCFalha.Text:= 'Sensores';
    end;
  2:
    begin
      lblResumoCFalha.Text:= 'Vazão';
    end;
  else
    begin
      lblResumoCFalha.Text:= 'Desconhecido';
    end;
  end;

  //Henrique Resumo
  contador:= 34;
  temp:= StrToInt(Copy(resposta, contador, 1));  //Status Caixa
  case temp of
  0:
    begin
      lblResumoHStatus.Text:= 'Cheia';
    end;
  1:
    begin
      lblResumoHStatus.Text:= 'Vazia';
    end;
  2:
    begin
      lblResumoHStatus.Text:= 'Normal';
    end;
  3:
    begin
      lblResumoHStatus.Text:= 'Enchendo';
    end;
  else
    begin
      lblResumoHStatus.Text:= 'Desconhecido';
    end;
  end;

  contador:= 47;
  temp:= StrToInt(Copy(resposta, contador, 1)); //Falha
  case temp of
  0:
    begin
      lblResumoHFalha.Text:= 'Normal';
    end;
  1:
    begin
      lblResumoHFalha.Text:= 'Sensores';
    end;
  2:
    begin
      lblResumoHFalha.Text:= 'Vazão';
    end;
  else
    begin
      lblResumoHFalha.Text:= 'Desconhecido';
    end;
  end;

end;

procedure TfrmMain.Atualizar();

var
tamanho: integer;

begin

  // var  (Como farei para desmembrar o Payload do MQTT
  // Source, Target : string;
  //Source := '12345678';
  //Target := Copy(Source, 3, 4);    // Target now = '3456'

   tamanho:= length(resposta);

   //and (tamanho > 49)   Inserir no teste

  if((conectado = 1) and (tamanho > 50))  then
    begin
      case pagina of
        1:
          begin
            DadosValderi();
          end;
        2:
          begin
            DadosCristiano();
          end;
        3:
          begin
            DadosHenrique();
          end;
        4:
          begin
            DadosResumo();
          end;
      end;
      //lblBotaoModo.Text:= 'Desabilitado';
  end
  else
    begin
      textoPadrao:= 'Desconhecido';
     case pagina of
        1:
          begin
            lblNome.Text:= 'VALDERI';
            lblStatus.Text:= textoPadrao;
            lblSensorNivelBaixo.Text:= textoPadrao;
            lblSensorNivelAlto.Text:= textoPadrao;
            lblFalha.Text:= textoPadrao;
            lblBotaoOnOff.Text:= textoPadrao;
          end;
        2:
          begin
            lblNome.Text:= 'CRISTIANO';
            lblStatus.Text:= textoPadrao;
            lblSensorNivelBaixo.Text:= textoPadrao;
            lblSensorNivelAlto.Text:= textoPadrao;
            lblFalha.Text:= textoPadrao;
            lblBotaoOnOff.Text:= textoPadrao;
          end;
        3:
          begin
            lblNome.Text:= 'HENRIQUE';
            lblStatus.Text:= textoPadrao;
            lblSensorNivelBaixo.Text:= textoPadrao;
            lblSensorNivelAlto.Text:= textoPadrao;
            lblFalha.Text:= textoPadrao;
            lblBotaoOnOff.Text:= textoPadrao;
          end;
        4:
          begin
            lblResumoVStatus.Text:= textoPadrao;
            lblResumoVFalha.Text:= textoPadrao;
            lblResumoCStatus.Text:= textoPadrao;
            lblResumoCFalha.Text:= textoPadrao;
            lblResumoHStatus.Text:= textoPadrao;
            lblResumoHFalha.Text:= textoPadrao;
          end;
      end;
    lblBotaoModo.Text:= textoPadrao;
    end;
end;



procedure TfrmMain.btnAjudaCaixaClick(Sender: TObject);
begin
  actAjuda.ExecuteTarget(Sender);
end;

procedure TfrmMain.btnMenuResumoClick(Sender: TObject);
begin
   actPrincipal.ExecuteTarget(Sender);
end;

procedure TfrmMain.btnTelefoneResumoClick(Sender: TObject);
begin
   actTelefone.ExecuteTarget(Sender);
end;

procedure TfrmMain.btnAjudaResumoClick(Sender: TObject);
begin
  actAjuda.ExecuteTarget(Sender);
end;

procedure TfrmMain.btnMenuTelefoneClick(Sender: TObject);
begin
  actPrincipal.ExecuteTarget(Sender);
end;

procedure TfrmMain.btnAjudaTelefoneClick(Sender: TObject);
begin
   actAjuda.ExecuteTarget(Sender);
end;

procedure TfrmMain.btnAvancarClick(Sender: TObject);
begin
  pagina:= pagina + 1;
  If(pagina > 3) then
  begin
    pagina:= 1;
  end;
  Atualizar();
end;

procedure TfrmMain.btnMenuAjudaClick(Sender: TObject);
begin
  actPrincipal.ExecuteTarget(Sender);
end;

procedure TfrmMain.btnTelefoneAjudaClick(Sender: TObject);
begin
   actTelefone.ExecuteTarget(Sender);
end;

procedure TfrmMain.btnValderiClick(Sender: TObject);
begin
    pagina:= 1;
    actCaixa.ExecuteTarget(Sender);
    Atualizar();
end;

procedure TfrmMain.btnHenriqueClick(Sender: TObject);
begin
  pagina:= 3;
  actCaixa.ExecuteTarget(Sender);
  Atualizar();
end;

procedure TfrmMain.btnCristianoClick(Sender: TObject);
begin
  pagina:= 2;
  actCaixa.ExecuteTarget(Sender);
  Atualizar();
end;

procedure TfrmMain.btnTelefoneMainClick(Sender: TObject);
begin
   actTelefone.ExecuteTarget(Sender);
end;

procedure TfrmMain.btnAjudaMainClick(Sender: TObject);
begin
   actAjuda.ExecuteTarget(Sender);
end;

procedure TfrmMain.btnResumoClick(Sender: TObject);
begin
  pagina:= 4;
  actResumo.ExecuteTarget(Sender);
  Atualizar();
end;

procedure TfrmMain.btnMenuCaixaClick(Sender: TObject);
begin
  actPrincipal.ExecuteTarget(Sender);
end;

procedure TfrmMain.btnTelefoneCaixaClick(Sender: TObject);
begin
  actTelefone.ExecuteTarget(Sender);
end;

end.
