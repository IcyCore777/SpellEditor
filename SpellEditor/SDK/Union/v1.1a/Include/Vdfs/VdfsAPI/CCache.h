#pragma once

#define cache_size (8192)

struct CCache
{
	HBuffer data [cache_size];
	uint32	baseAddr;
	uint32	realSize;
};