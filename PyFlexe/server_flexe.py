from concurrent import futures
import logging
from optparse import OptionParser

import grpc
import core.proto.flexe_pb2_grpc as flexe_pb2_grpc
from core.application.GenericApp import GenericApp
from core.application.VivaBemApp import VivaBemApp
from core.application.ColisaoApp import ColisaoApp

import sys
import os

def serve(ip_server, application):
    print("+-------------------------------+")
    print("|       GRPC Server Start!      |")
    print("+-------------------------------+")
    print("Server IP address: " + ip_server)
    print()
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10),
    options = [
        ('grpc.max_send_message_length', -1),
        ('grpc.max_receive_message_length', -1),
        ('grpc.client_idle_timeout_ms', 7200000),
        ('grpc.keepalive_timeout_ms', 7200000),
        ('grpc.grpclb_call_timeout_ms', 7200000)
    ])

    if application == "GenericApp":
        flexe_pb2_grpc.add_FlexeServicer_to_server(GenericApp(), server)
    elif application == "VivaBemApp":
        flexe_pb2_grpc.add_FlexeServicer_to_server(VivaBemApp(), server)
        
    elif application == "ColisaoApp":
        flexe_pb2_grpc.add_FlexeServicer_to_server(ColisaoApp(), server)
    
    server.add_insecure_port(ip_server)
    server.start()
    server.wait_for_termination()

if __name__ == '__main__':
    parser = OptionParser()
    parser.add_option("-i", "--ip",    		        dest="ip_address",         default='127.0.0.1:5000',  help="Strategy of the federated learning",            metavar="STR")
    parser.add_option("-a", "--application",        dest="application",        default='GenericApp',      help="Define the Application of federated learning",  metavar="STR")
    (opt, args) = parser.parse_args()
    logging.basicConfig()
    serve(opt.ip_address, opt.application)
