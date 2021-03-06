/**
 * @file charging_addresses.h A class containing a subscriber's charging
 * addresses.
 *
 * Project Clearwater - IMS in the Cloud
 * Copyright (C) 2013  Metaswitch Networks Ltd
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version, along with the "Special Exception" for use of
 * the program along with SSL, set forth below. This program is distributed
 * in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details. You should have received a copy of the GNU General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * The author can be reached by email at clearwater@metaswitch.com or by
 * post at Metaswitch Networks Ltd, 100 Church St, Enfield EN2 6BQ, UK
 *
 * Special Exception
 * Metaswitch Networks Ltd  grants you permission to copy, modify,
 * propagate, and distribute a work formed by combining OpenSSL with The
 * Software, or a work derivative of such a combination, even if such
 * copying, modification, propagation, or distribution would otherwise
 * violate the terms of the GPL. You must comply with the GPL in all
 * respects for all of the code used other than OpenSSL.
 * "OpenSSL" means OpenSSL toolkit software distributed by the OpenSSL
 * Project and licensed under the OpenSSL Licenses, or a work based on such
 * software and licensed under the OpenSSL Licenses.
 * "OpenSSL Licenses" means the OpenSSL License and Original SSLeay License
 * under which the OpenSSL Project distributes the OpenSSL toolkit software,
 * as those licenses appear in the file LICENSE-OPENSSL.
 */

#ifndef CHARGING_ADDRESSES_H__
#define CHARGING_ADDRESSES_H__

#include <string>
#include <deque>

/// An object containing a subscriber's charging addresses.
class ChargingAddresses
{
public:
  /// Default constructor.
  inline ChargingAddresses() {}

  /// Constructor which takes CCFs and ECFs.
  inline ChargingAddresses(std::deque<std::string> ccfs,
                           std::deque<std::string> ecfs) : ccfs(ccfs), ecfs(ecfs) {}


  /// Double ended queues of collect charging function addresses and event
  /// charging function addresses. These are stored in priority order, and
  /// they are stored in the format given by the provisioning server
  /// (normally the HSS).
  std::deque<std::string> ccfs;
  std::deque<std::string> ecfs;

  /// Helper function to determine whether we have any charging addresses.
  inline bool empty() const { return (ccfs.empty()) && (ecfs.empty()); }

  /// Convert the charging functions into a string to display in logs
  std::string log_string()
  {
    std::string log_str;

    if (!ccfs.empty())
    {
      log_str.append("Primary CCF: ").append(ccfs[0]);

      if (ccfs.size() > 1)
      {
        log_str.append(", Secondary CCF: ").append(ccfs[1]);
      }
    }
    if (!ecfs.empty())
    {
      if (!ccfs.empty())
      {
        log_str.append(", ");
      }

      log_str.append("Primary ECF: ").append(ecfs[0]);

      if (ecfs.size() > 1)
      {
        log_str.append(", Secondary ECF: ").append(ecfs[1]);
      }
    }

    return log_str;
  }
};

#endif
