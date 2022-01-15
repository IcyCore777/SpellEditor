#include "stdafx.h"
#include "Control.h"

zCVob	    *editVob = 0;
zCVob		*targetVob = 0;

//zVEC3 external Operators
inline zVEC3 operator * (const zREAL d, const zVEC3& a)
{
	return a*d;
}
//get nearest vob 
zCVob *GetNearVob()
{
	if (!editVob) return 0;
	
	zTBBox3D box;
	box.maxs = editVob->GetPositionWorld() + zVEC3(2000, 2000, 2000);
	box.mins = editVob->GetPositionWorld() - zVEC3(2000, 2000, 2000);
	zCArray<zCVob*>resVobList;
	ogame->GetWorld()->CollectVobsInBBox3D(resVobList, box);

	for (int i = 0; i<resVobList.GetNumInList(); i++) {
		if (resVobList[i]->GetVobType() == zVOB_TYPE_NSC && resVobList[i] != oCNpc::player) return resVobList[i];
	}
	return 0;
}

//create edit vob
void SetEditVob()
{
	if (editVob)
	{
		//	editVob->RemoveVobFromWorld();
		//	zRELEASE(editVob);
	}
	editVob = ogame->GetGameWorld()->SearchVobByName("FX_111_CASTER");
	targetVob = ogame->GetGameWorld()->SearchVobByName("FX_112_TARGET");
	if (!editVob)
		editVob = ogame->GetSpawnManager()->SpawnNpc(parser->GetIndex("FX_111_CASTER"), "WP_CASTER", 0.0f);
	if (!targetVob)
		targetVob = ogame->GetSpawnManager()->SpawnNpc(parser->GetIndex("FX_112_TARGET"), "WP_TARGET_2", 0.0f);

	if (editVob == 0)
	{
		editVob = zNEW(zCVob);
		zCCamera::activeCam->GetVob()->GetHomeWorld()->AddVob(editVob);
		editVob->SetVobName("help fx edit vob");
		editVob->SetVisual("invisible_zCVob.3ds");
		editVob->SetShowVisual(TRUE);
		editVob->SetCollDet(FALSE);
		editVob->SetSleeping(FALSE);
		editVob->SetPhysicsEnabled(FALSE);
		editVob->SetPositionWorld(zCCamera::activeCam->GetVob()->GetPositionWorld() + 150 * zCCamera::activeCam->GetVob()->GetAtVectorWorld());
	}
}


void oCVisualFX::InitParser()
{
	if (!fxParser)
	{
		zerr->Message("C: *** Visual FX Implementation " + zSTRING("v0.5"));
		fxParser = zNEW(zCParser());
	}
	else  		   fxParser->Reset();

	zBOOL reparsevis = TRUE;
	zCParser::SetEnableParsing(reparsevis);

	zSTRING filename = "";
	if (zgameoptions)
		filename = zgameoptions->ReadString("FILES", "VisualEffects");
	if (filename.IsEmpty())
		filename = "System\\VisualFx";
	zERR_MESSAGE(4, 0, "N: VFX: Loading file " + filename + ".src or .dat");

	fxParser->Parse(filename + ".src");
	fxParser->CreatePCode();
	fxParser->CheckClassSize(zSTRING("C_PARTICLEFXEMITKEY"), oCEmitterKey::GetScriptClassSize());
	fxParser->CheckClassSize(zSTRING("CFX_BASE"), oCVisualFX::GetScriptClassSize());

	zCParser::SetEnableParsing(FALSE);
};

void zCParticleFX::ParseParticleFXScript_union() {

	// [BENDLIN] AddonMOD
	zSTRING filename = "";
	if (zgameoptions)
		filename = zgameoptions->ReadString("FILES", "ParticleEffects");
	if (filename.IsEmpty())
		filename = "System\\PARTICLEFX";
	zERR_MESSAGE(3, zERR_BEGIN, "D: PFX: Loading file " + filename + ".src or .dat");

	// FIXME: wann parser loeschen, wann nicht ????

	// Symbole: klassen, klassenVar, instance, protos, funcs, globvars
	if (!s_pfxParser)	s_pfxParser = zNEW(zCParser());
	else				s_pfxParser->Reset();
	const int dscriptClassSize = int(&(s_emitterDummyDefault.endOfDScriptPart)) - int(&s_emitterDummyDefault);
	zCParser::SetEnableParsing(TRUE);
	s_pfxParser->Parse(filename + ".src");
	s_pfxParser->CreatePCode();
	s_pfxParser->CheckClassSize(zSTRING("C_PARTICLEFX"), dscriptClassSize);
	zCParser::SetEnableParsing(FALSE);
	
	// eine evtl. vorher schon vorhandene Emitter-Preset-List loeschen
	for (int i = 0; i < s_emitterPresetList.GetNumInList(); i++)
	{
		s_emitterPresetList[i]->Reset();
		delete s_emitterPresetList[i];
	}

	s_emitterPresetList.EmptyList();

	// Alle C_ParticleFX Instanzen aus den Scripten holen & als Presets initialisieren
	zSTRING instanceName;
	int		cindex = s_pfxParser->GetIndex(zSTRING("C_PARTICLEFX"));
	int		pos = 0;
	while (pos >= 0) {
		pos = s_pfxParser->GetInstance(cindex, pos + 1);
		zCPar_Symbol *sym = s_pfxParser->GetSymbol(pos);
		if (sym) {
			instanceName = sym->name;
			zCParticleEmitter *emitter = zNEW(zCParticleEmitter);
			s_pfxParser->CreateInstance(instanceName, emitter);

			emitter->particleFXName = instanceName;
			s_emitterPresetList.Insert(emitter);
			//			zerr.Message ("D: PFX: "+instanceName);
		};
	};
	s_emitterPresetList.QuickSort();

	// UpdateInternals() darf erst erfolgen, wenn alle Presets da, sind, damit
	// interne Referenzen aufgeloest werden koennen
	for (int i = 0; i<s_emitterPresetList.GetNumInList(); i++) {
		s_emitterPresetList[i]->UpdateInternals();
	};
	CMainFrame::mainframe->wndControl->UpdatePfx();
	//
	//	delete pfxParser;
	zERR_MESSAGE(3, zERR_END, "D: PFX: Num ParticleFX: " + zSTRING(s_emitterPresetList.GetNumInList()));
};


void OffsetChildWindow(CWnd* child, int dx, int dy, int dw, int dh)
{
	if (!child) return;
	if (!child->GetParent()) return;
	if (!IsWindow(child->m_hWnd)) return;

	//find child window's coordinates relative to top-left of parent
	CRect rc;
	child->GetWindowRect(&rc);
	CPoint p(0, 0);
	ScreenToClient(child->GetParent()->GetSafeHwnd(), &p);
	rc.OffsetRect(p);

	//prevent negative size
	if ((rc.Width() + dw) < 0) dw = -rc.Width();
	if ((rc.Height() + dh) < 0) dh = -rc.Height();

	child->SetWindowPos(0, rc.left + dx, rc.top + dy, rc.Width() + dw, rc.Height() + dh, SWP_NOZORDER);
	child->Invalidate(FALSE);
}
