/*!
   \file Memory.h
   \brief Basic TLM-2 memory model
   \author Màrius Montón
   \date August 2018
*/

#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <iostream>
#include <fstream>

#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "systemc"

#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"

using namespace sc_core;
using namespace sc_dt;
using namespace std;

/**
 * @brief Basic TLm-2 memory
 */
class Memory: sc_module {
public:
  // TLM-2 socket, defaults to 32-bits wide, base protocol
  tlm_utils::simple_target_socket<Memory> socket;

  enum { SIZE = 1024 };
  const sc_time LATENCY;

  Memory(sc_module_name name, string filename);

  // TLM-2 blocking transport method
  virtual void b_transport( tlm::tlm_generic_payload& trans, sc_time& delay );

  // *********************************************
  // TLM-2 forward DMI method
  // *********************************************

  virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans,
                                  tlm::tlm_dmi& dmi_data);

  void invalidation_process();

  // *********************************************
  // TLM-2 debug transport method
  // *********************************************

  virtual unsigned int transport_dbg(tlm::tlm_generic_payload& trans);

  int mem[SIZE];

  /**
   * Reads file and stores in Code Memory. Uses propietary file format
   * @brief Reads file and stores in Code Memory
   * @param filename File name
   */
  virtual void readCustomHexFile(string filename);

  /**
   * @brief Read Intel hex file
   * @param filename file name to read
   */
  virtual void readHexFile(string filename);
};
 #endif /* __MEMORY_H__ */
