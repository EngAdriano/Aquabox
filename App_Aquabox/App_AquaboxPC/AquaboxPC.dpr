program AquaboxPC;

uses
  System.StartUpCopy,
  FMX.Forms,
  frmPrincipal in 'frmPrincipal.pas' {frmMain};

{$R *.res}

begin
  Application.Initialize;
  Application.FormFactor.Orientations := [TFormOrientation.Portrait];
  Application.CreateForm(TfrmMain, frmMain);
  Application.Run;
end.
