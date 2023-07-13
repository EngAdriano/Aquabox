program Aquabox;

uses
  System.StartUpCopy,
  FMX.Forms,
  frmPrincipal in 'frmPrincipal.pas' {frmMain},
  UNetworkState in 'Source\UNetworkState.pas',
  UNetworkState.Android in 'Source\Android\UNetworkState.Android.pas',
  UBroadcastReceiver in 'Source\Android\BroadcastReceiver\UBroadcastReceiver.pas',
  UNetworkStateBroadcastReceiver in 'Source\Android\BroadcastReceiver\UNetworkStateBroadcastReceiver.pas',
  CaptiveNetwork in 'Source\iOS\CaptiveNetwork.pas',
  SCNetworkReachability in 'Source\iOS\SCNetworkReachability.pas',
  UNetworkState.iOS in 'Source\iOS\UNetworkState.iOS.pas',
  frmAbertura in 'frmAbertura.pas' {frmSplash};

{$R *.res}

begin
  Application.Initialize;
  Application.FormFactor.Orientations := [TFormOrientation.Portrait];
  Application.CreateForm(TfrmSplash, frmSplash);
  Application.Run;
end.
