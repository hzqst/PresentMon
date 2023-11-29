// Copyright (C) 2022 Intel Corporation
// SPDX-License-Identifier: MIT
#pragma once
#ifdef PRESENTMONAPI2_EXPORTS
#define PRESENTMON_API_EXPORT __declspec(dllexport)
#else
#define PRESENTMON_API_EXPORT __declspec(dllimport)
#endif

#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif

	enum PM_STATUS // **
	{
		PM_STATUS_SUCCESS,
		PM_STATUS_FAILURE,
		PM_STATUS_SESSION_NOT_OPEN,
	};

	enum PM_METRIC // **
	{
		PM_METRIC_DISPLAYED_FPS,
		PM_METRIC_PRESENTED_FPS,
		PM_METRIC_FRAME_TIME,
		PM_METRIC_PRESENT_MODE,
		PM_METRIC_GPU_POWER,
		PM_METRIC_CPU_UTILIZATION,
		PM_METRIC_GPU_FAN_SPEED,
		PM_METRIC_PROCESS_NAME,
		PM_METRIC_GPU_BUSY_TIME,
		PM_METRIC_CPU_BUSY_TIME,
		PM_METRIC_CPU_WAIT_TIME,
		PM_METRIC_CPU_CORE_UTILITY,
		PM_METRIC_INPUT_LATENCY_TIME,
		PM_METRIC_DISPLAY_BUSY_TIME,
	};

	enum PM_METRIC_TYPE
	{
		PM_METRIC_TYPE_DYNAMIC,
		PM_METRIC_TYPE_STATIC,
	};

	enum PM_DEVICE_VENDOR
	{
		PM_DEVICE_VENDOR_INTEL,
		PM_DEVICE_VENDOR_NVIDIA,
		PM_DEVICE_VENDOR_AMD,
		PM_DEVICE_VENDOR_UNKNOWN
	};

	enum PM_PRESENT_MODE
	{
		PM_PRESENT_MODE_HARDWARE_LEGACY_FLIP,
		PM_PRESENT_MODE_HARDWARE_LEGACY_COPY_TO_FRONT_BUFFER,
		PM_PRESENT_MODE_HARDWARE_INDEPENDENT_FLIP,
		PM_PRESENT_MODE_COMPOSED_FLIP,
		PM_PRESENT_MODE_HARDWARE_COMPOSED_INDEPENDENT_FLIP,
		PM_PRESENT_MODE_COMPOSED_COPY_WITH_GPU_GDI,
		PM_PRESENT_MODE_COMPOSED_COPY_WITH_CPU_GDI,
		PM_PRESENT_MODE_UNKNOWN
	};

	enum PM_PSU_TYPE
	{
		PM_PSU_TYPE_NONE,
		PM_PSU_TYPE_PCIE,
		PM_PSU_TYPE_6PIN,
		PM_PSU_TYPE_8PIN
	};

	enum PM_UNIT
	{
		PM_UNIT_DIMENSIONLESS,
		PM_UNIT_BOOLEAN,
		PM_UNIT_FPS,
		PM_UNIT_MILLISECONDS,
		PM_UNIT_PERCENT,
		PM_UNIT_WATTS,
		PM_UNIT_SYNC_INTERVAL,
		PM_UNIT_VOLTS,
		PM_UNIT_MEGAHERTZ,
		PM_UNIT_CELSIUS,
		PM_UNIT_RPM,
		PM_UNIT_BPS,
		PM_UNIT_BYTES,
	};

	enum PM_STAT
	{
		PM_STAT_AVG,
		PM_STAT_PERCENTILE_99,
		PM_STAT_PERCENTILE_95,
		PM_STAT_PERCENTILE_90,
		PM_STAT_MAX,
		PM_STAT_MIN,
		PM_STAT_RAW,
	};

	enum PM_DATA_TYPE
	{
		PM_DATA_TYPE_DOUBLE,
		PM_DATA_TYPE_INT32,
		PM_DATA_TYPE_UINT32,
		PM_DATA_TYPE_ENUM,
		PM_DATA_TYPE_STRING,
	};

	enum PM_GRAPHICS_RUNTIME
	{
		PM_GRAPHICS_RUNTIME_UNKNOWN,
		PM_GRAPHICS_RUNTIME_DXGI,
		PM_GRAPHICS_RUNTIME_D3D9,
	};

	enum PM_DEVICE_TYPE
	{
		PM_DEVICE_TYPE_INDEPENDENT,
		PM_DEVICE_TYPE_GRAPHICS_ADAPTER,
	};

	enum PM_METRIC_AVAILABILITY
	{
		PM_METRIC_AVAILABILITY_AVAILABLE,
		PM_METRIC_AVAILABILITY_UNAVAILABLE,
	};

	enum PM_ENUM
	{
		PM_ENUM_STATUS,
		PM_ENUM_METRIC,
		PM_ENUM_METRIC_TYPE,
		PM_ENUM_DEVICE_VENDOR,
		PM_ENUM_PRESENT_MODE,
		PM_ENUM_PSU_TYPE,
		PM_ENUM_UNIT,
		PM_ENUM_STAT,
		PM_ENUM_DATA_TYPE,
		PM_ENUM_GRAPHICS_RUNTIME,
		PM_ENUM_DEVICE_TYPE,
		PM_ENUM_METRIC_AVAILABILITY,
	};

	struct PM_INTROSPECTION_STRING
	{
		const char* pData;
	};

	struct PM_INTROSPECTION_OBJARRAY
	{
		const void** pData;
		size_t size;
	};

	struct PM_INTROSPECTION_ENUM_KEY
	{
		PM_ENUM enumId;
		int value;
		PM_INTROSPECTION_STRING* pSymbol;
		PM_INTROSPECTION_STRING* pName;
		PM_INTROSPECTION_STRING* pShortName;
		PM_INTROSPECTION_STRING* pDescription;
	};

	struct PM_INTROSPECTION_ENUM
	{
		PM_ENUM id;
		PM_INTROSPECTION_STRING* pSymbol;
		PM_INTROSPECTION_STRING* pDescription;
		PM_INTROSPECTION_OBJARRAY* pKeys;
	};

	struct PM_INTROSPECTION_DEVICE
	{
		uint32_t id;
		PM_DEVICE_TYPE type;
		PM_DEVICE_VENDOR vendor;
		PM_INTROSPECTION_STRING* pName;
	};

	struct PM_INTROSPECTION_DEVICE_METRIC_INFO
	{
		uint32_t deviceId;
		PM_METRIC_AVAILABILITY availability;
		uint32_t arraySize;
	};

	struct PM_INTROSPECTION_DATA_TYPE_INFO
	{
		PM_DATA_TYPE type;
		PM_ENUM enumId;
	};

	struct PM_INTROSPECTION_STAT_INFO
	{
		PM_STAT stat;
	};

	struct PM_INTROSPECTION_METRIC
	{
		PM_METRIC id;
		PM_METRIC_TYPE type;
		PM_UNIT unit;
		PM_INTROSPECTION_DATA_TYPE_INFO* pTypeInfo;
		PM_INTROSPECTION_OBJARRAY* pStatInfo;
		PM_INTROSPECTION_OBJARRAY* pDeviceMetricInfo;
	};

	struct PM_INTROSPECTION_ROOT
	{
		PM_INTROSPECTION_OBJARRAY* pMetrics;
		PM_INTROSPECTION_OBJARRAY* pEnums;
		PM_INTROSPECTION_OBJARRAY* pDevices;
	};

	struct PM_QUERY_ELEMENT
	{
		PM_METRIC metric;
		PM_STAT stat;
		uint32_t deviceId;
		uint32_t arrayIndex;
		uint64_t dataOffset;
		uint64_t dataSize;
	};

	typedef struct PM_DYNAMIC_QUERY* PM_DYNAMIC_QUERY_HANDLE;

	PRESENTMON_API_EXPORT PM_STATUS pmOpenSession(uint32_t process_id);
	PRESENTMON_API_EXPORT PM_STATUS pmCloseSession();
	PRESENTMON_API_EXPORT PM_STATUS pmEnumerateInterface(const PM_INTROSPECTION_ROOT** ppInterface);
	PRESENTMON_API_EXPORT PM_STATUS pmFreeInterface(const PM_INTROSPECTION_ROOT* pInterface);
	PRESENTMON_API_EXPORT PM_STATUS pmRegisterDynamicQuery(PM_DYNAMIC_QUERY_HANDLE* pHandle, PM_QUERY_ELEMENT* pElements, uint64_t numElements, double windowSizeMs, double metricOffsetMs = 0.f);
	PRESENTMON_API_EXPORT PM_STATUS pmFreeDynamicQuery(PM_DYNAMIC_QUERY_HANDLE handle);
	PRESENTMON_API_EXPORT PM_STATUS pmPollDynamicQuery(PM_DYNAMIC_QUERY_HANDLE handle, uint8_t* pBlob, uint32_t* numSwapChains);
	PRESENTMON_API_EXPORT PM_STATUS pmPollStaticQuery(const PM_QUERY_ELEMENT* pElement, uint8_t* pBlob);
	

	/////// draft functions ///////
	
	//// process tracking (start "streaming" frame events) function
	// start streaming
	// stop streaming
	
	//// consuming frame events
	// read frames
	
	//// setting global middleware settings
	// offset (could this be per call? or set in the dynamic query registration?)
	
	//// setting global service settings
	// rate of polling telemetry (set per device?)
	
	//// offline etl streaming session
	// input the file
	// 



#ifdef __cplusplus
} // extern "C"
#endif