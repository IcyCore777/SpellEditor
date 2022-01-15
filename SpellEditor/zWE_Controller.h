#pragma once


#define DllExport __declspec(dllexport)

enum zEVobMotionMode {
	zMM_NONE,
	zMM_MOVE,
	zMM_ROTATE,
	zMM_SCALE
};

enum zEVobMotionHeading {
	zMH_WORLD,
	zMH_LOCALE,
	zMH_VIEW
};

enum zEVobCollisionMode {
	zVC_DEFAULT,
	zVC_DISABLED,
	zVC_ENABLED
};

enum zECamMotionMode {
	zCM_DISABLED,
	zCM_ENABLED
};

enum zEPickMode {
	zPM_DISABLED,
	zPM_VOBS,
	zPM_POLYS
};

enum zEPickMethod {
	zPM_CURSOR,
	zPM_CROSSHAIR
};

struct zTWE_ControllerEvents {
	Common::Array<zCVob*>		SelectedVobs;
	zCVob*						PickedVob;
	zCPolygon*					PickedPoly;
	zEPickMode					PickMode;
	zEPickMethod				PickMethod;
	zEVobMotionMode				MotionMode;
	zEVobMotionHeading			MotionHeading;
	zEVobCollisionMode			CollisionMode;
	zECamMotionMode				CameraMoving;
	zVEC2						CursorPosition;
	float						GizmoScale;
	HWND						mainframe;
};

extern DllExport zTWE_ControllerEvents ControllerEvents;


