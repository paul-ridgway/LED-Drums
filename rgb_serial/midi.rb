require "unimidi"

# Prompts the user to select a midi input
# Sends an inspection of the first 10 messages messages that input receives to standard out

num_messages = 10000000

# Prompt the user
input = UniMIDI::Input.gets

# using their selection...

puts "send some MIDI to your input now..."

num_messages.times do
  m = input.gets
  puts(m)
end

puts "finished"
