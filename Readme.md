# STM32 Software Test Bench with Raspberry Pi and gRPC

## Project Overview

This project implements a software test bench to evaluate the behavior of an STM32 microcontroller using a Raspberry Pi as a controller. The Raspberry Pi sends signals to the STM32, reads the response, measures the duration, and sends the results back to a PC via Ethernet. The PC hosts a GUI that communicates with the Raspberry Pi using gRPC to trigger and monitor tests.

## System Architecture

The system consists of three main components:
1. **PC with GUI**: Acts as the client, sending commands to the Raspberry Pi via gRPC to start testing.
2. **Raspberry Pi**: Acts as the server, sending signals to the STM32 and reading the results. It also measures the time taken by the STM32 to respond to specific inputs.
3. **STM32 Microcontroller**: The target device for testing. Its behavior is observed and measured based on the input/output pin states.

### Communication Flow:
- The PC sends test commands to the Raspberry Pi using gRPC over Ethernet.
- The Raspberry Pi interacts with the STM32 through GPIO pins, triggering specific behaviors and measuring the response time.
- The results are sent back to the PC, which displays them in the GUI.

## Technologies Used

- **gRPC**: A remote procedure call framework used for communication between the PC (client) and the Raspberry Pi (server).
- **Protocol Buffers (protobufs)**: Used for defining the messages and services for gRPC.
- **STM32**: The microcontroller being tested.
- **Raspberry Pi**: Acts as a hardware test controller, running the gRPC server.
- **Ethernet**: For communication between the PC and Raspberry Pi.
- **Python**: Programming language used for both client and server code.

## Project Setup

### 1. Raspberry Pi - gRPC Server

The Raspberry Pi acts as the server, listening for commands from the PC and running tests on the STM32. To set up the Raspberry Pi:

- Install gRPC and the necessary dependencies on the Raspberry Pi:
  ```bash
  pip install grpcio grpcio-tools

- Define the service and message structure in a `.proto` file:

  ```python
  protoCopy codesyntax = "proto3";
  
  service TestService {
    rpc StartTest (TestRequest) returns (TestResponse);
  }
  
  message TestRequest {
    string test_name = 1;
  }
  
  message TestResponse {
    string result = 1;
    int32 duration_ms = 2;
  }
  ```

- Use `protoc` to generate the gRPC Python code from the `.proto` file:

  ```python
  python -m grpc_tools.protoc -I. --python_out=. --grpc_python_out=. test_service.proto
  ```

- Implement the server on the Raspberry Pi:

  ```python
  pythonCopy codeimport grpc
  from concurrent import futures
  import test_service_pb2
  import test_service_pb2_grpc
  
  class TestService(test_service_pb2_grpc.TestServiceServicer):
      def StartTest(self, request, context):
          result = perform_test(request.test_name)
          duration = measure_test_duration()
          return test_service_pb2.TestResponse(result=result, duration_ms=duration)
  
  def serve():
      server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
      test_service_pb2_grpc.add_TestServiceServicer_to_server(TestService(), server)
      server.add_insecure_port('[::]:50051')
      server.start()
      server.wait_for_termination()
  
  if __name__ == "__main__":
      serve()
  ```

### 2. PC - gRPC Client

The PC sends commands to the Raspberry Pi to trigger tests and retrieve the results.

- Install gRPC on the PC:

  ```bash
  pip install grpcio grpcio-tools
  ```

- Implement the client code:

  ```python
  pythonCopy codeimport grpc
  import test_service_pb2
  import test_service_pb2_grpc
  
  def start_test(test_name):
      channel = grpc.insecure_channel('raspberrypi:50051')
      stub = test_service_pb2_grpc.TestServiceStub(channel)
      request = test_service_pb2.TestRequest(test_name=test_name)
      response = stub.StartTest(request)
      print(f"Test Result: {response.result}, Duration: {response.duration_ms} ms")
  ```

- The GUI on the PC will call this function when the user presses the Start button.

### 3. STM32

The STM32 microcontroller is the target device for testing. The Raspberry Pi sends signals to the STM32 pins and reads the corresponding output to verify the expected behavior.

## How to Run

1. On the Raspberry Pi, start the gRPC server:

   ```bash
   python server.py
   ```

2. On the PC, run the client and trigger a test:

   ```bash
   python client.py
   ```

3. Use the GUI on the PC to start and monitor the test.

## Future Improvements

- **Advanced Test Cases**: Add more complex test scenarios involving different STM32 behaviors.
- **Real-time Monitoring**: Implement real-time monitoring of the test status in the GUI.
- **Error Handling**: Add more robust error handling for network issues or hardware failures.

## Conclusion

This project demonstrates how to set up a software test bench using gRPC for communication between a PC and Raspberry Pi to test the behavior of an STM32 microcontroller. The system leverages gRPC for efficient, scalable communication and provides an easy way to test embedded systems.

```
This markdown file (`README.md`) gives a clear explanation of the project setup, technologies, and step-by-step instructions for implementing the system. Let me know if you'd like to make any adjustments!
```