#ifndef __SWSPI__
#define __SWSPI__

/* 
 * Data is clocked out from MSB and clocked into from LSB usually
 * CPOL - clock is 0 or 1 at start(when select line goes low)
 * CPHA - 0, sample on the first(leading) clock edge (could be rising/falling)
		  and propagate one the trailing edge
 * CPHA - 1, Propagate on the first(leading) clock edge (could be rising/falling)
		  and sample on the trailing edge.
 * This gives 4 modes of operation. Usually signals should be held at reception
 * side for at least half a cycle before the next transition
 */

/**
 * @brief GPIO pin type
 */
typedef struct _PIN_t {
	uint32_t port;
	uint32_t pin;
}
PIN_t;

						
/**
 * @brief pins used for software SPI emulation
 */
typedef struct _SW_SPI_t {
	PIN_t sclk;	
	PIN_t miso;
	PIN_t mosi;
	PIN_t ssel;
	uint8_t cpol; 	/* 0 or 1 */
	uint8_t cpha; 	/* 0 or 1 */
	uint32_t sclkFreq;	/* SPI master comms freq */
	float clkH_us;	/* calculated as half of period(Do not assign) */
	float clkL_us;	/* calculated as half of period(Do not assign) */
	bool msbFirst;
}
SW_SPI_t;

typedef struct _SPI_data_t {
	uint8_t *dout;		/* Output data buffer */
	uint8_t *din;		/* Input data buffer */
	uint32_t numSPIBytes;	/* Total SPI bytes. As SPI is duplex, read and write
						   happens at same time. dout and din should point to
						   memory of atleast 'numBytes' size.*/
}
SPI_data_t;

/**
  * @brief Init bit bashing SPI
  * @param master instance spi
  * @return nothing
  * @note Only calculates clkHigh_us and clkLow_us from sclkfreq
  * 		Supply all other fields to function.
  */
void SW_SPI_MasterInit(SW_SPI_t *pSPI);

/**
  * @brief Select slave connected to master spi instance @param spi
  * @note Each master is connected to only one slave. So select 'selects'
  * 	  that slave by making ssel low
  */
void SW_SPI_Sel(SW_SPI_t *pSPI);

/**
  * @brief DeSelect slave connected to master spi instance @param spi
  * @note Each master is connected to only one slave. So Deselect 'deselects'
  * 	  that slave by making ssel high
  */
void SW_SPI_Desel(SW_SPI_t *pSPI);


/**
  * @brief Send(clock out) and receive(clock in) on byte at same time
  * @param master instance spi
  * @param spiData
  * @return nothing (SPI data read will be in spiData->din if requested)
  */
void SW_SPI_MasterTfr(SW_SPI_t *pSPI, SPI_data_t *pSPIData);


#endif /* __SWSPI__ */
