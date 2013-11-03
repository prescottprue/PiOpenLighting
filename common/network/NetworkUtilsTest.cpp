/*
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * NetworkUtilsTest.cpp
 * Test fixture for the NetworkUtils class
 * Copyright (C) 2005-2009 Simon Newton
 */

#include <cppunit/extensions/HelperMacros.h>

#include <string>

#include "ola/network/NetworkUtils.h"
#include "ola/Logging.h"
#include "ola/testing/TestUtils.h"



using ola::network::HardwareAddressToString;
using ola::network::HostToLittleEndian;
using ola::network::HostToNetwork;
using ola::network::LittleEndianToHost;
using ola::network::NetworkToHost;

class NetworkUtilsTest: public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(NetworkUtilsTest);
  CPPUNIT_TEST(testHardwareAddressToString);
  CPPUNIT_TEST(testToFromNetwork);
  CPPUNIT_TEST(testToFromLittleEndian);
  CPPUNIT_TEST_SUITE_END();

  public:
    void testHardwareAddressToString();
    void testToFromNetwork();
    void testToFromLittleEndian();
};

CPPUNIT_TEST_SUITE_REGISTRATION(NetworkUtilsTest);


/*
 * Check that HardwareAddressToString works
 */
void NetworkUtilsTest::testHardwareAddressToString() {
  uint8_t hw_address[ola::network::MAC_LENGTH] = {
    0x0, 0xa, 0xff, 0x10, 0x25, 0x4};
  const std::string mac_address = HardwareAddressToString(hw_address);
  OLA_ASSERT_EQ(std::string("00:0a:ff:10:25:04"), mac_address);
}


/*
 * Check that we can convert to/from network byte order
 */
void NetworkUtilsTest::testToFromNetwork() {
  uint8_t v1 = 10;
  OLA_ASSERT_EQ(v1, HostToNetwork(v1));
  OLA_ASSERT_EQ(v1, NetworkToHost(HostToNetwork(v1)));

  uint16_t v2 = 0x0102;
  OLA_ASSERT_EQ(v2, NetworkToHost(HostToNetwork(v2)));

  uint32_t v3 = 0x01020304;
  OLA_ASSERT_EQ(v3, NetworkToHost(HostToNetwork(v3)));
}


/*
 * Check that we can convert to/from little endian order
 */
void NetworkUtilsTest::testToFromLittleEndian() {
  uint8_t v1 = 10;
  OLA_ASSERT_EQ(v1, HostToLittleEndian(v1));
  OLA_ASSERT_EQ(v1, LittleEndianToHost(HostToLittleEndian(v1)));

  uint16_t v2 = 0x0102;
  OLA_ASSERT_EQ(v2, LittleEndianToHost(HostToLittleEndian(v2)));

  uint32_t v3 = 0x01020304;
  OLA_ASSERT_EQ(v3, LittleEndianToHost(HostToLittleEndian(v3)));
}
